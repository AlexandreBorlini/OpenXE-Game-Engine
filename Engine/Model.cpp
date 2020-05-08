#include "Model.h"

void Model::use(Camera camera) {

	shader.use();

	shader.setMatrix4("model", transform.getTransformResultMatrix());
	shader.setMatrix4("projection", camera.projection);
	shader.setMatrix4("view", camera.view);

	glm::mat4 view = glm::mat4(1.f);

	view[3][2] = -3.f;

	glm::vec4 worldLight = view * glm::vec4(.0f, .0f, 3.0f, 1.0f);

	glUniform4fv(glGetUniformLocation(shader.ID, "Light.Position"), 1, &worldLight[0]);

	shader.setVector3("Material.Kd", Vector3(0.9f, 0.5f, 0.3f));
	shader.setVector3("Light.Ld", Vector3(1.0f, 1.0f, 1.0f));

	shader.setVector3("Material.Ka", Vector3(0.9f, 0.5f, 0.3f));
	shader.setVector3("Light.La", Vector3(0.4f, 0.4f, 0.4f));

	shader.setVector3("Material.Ks", Vector3(0.8f, 0.8f, 0.8f));
	shader.setVector3("Light.Ls", Vector3(1.0f, 1.0f, 1.0f));

	shader.setFloat("Material.Shininess", 2.0f);

	for (unsigned int i = 0; i < meshes.size(); i++) {

		meshes[i].draw(shader);
	}
}

void Model::loadModel(string path) {

	Assimp::Importer importer;		// Struct importer

							 	    // Triangula o que não for triângulo   // Inverte Y das texturas que estiverem erradas
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); // Lê o arquivo

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {

		std::cout << "ERRO NO ASSIMP: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	processNode( scene->mRootNode, scene);										// Função recursiva para processar os nodes
}																				// Pega o rootNode pois os nodes são hierarquizados como children

void Model::processNode(aiNode *node, const aiScene *scene) {

	for (unsigned int i = 0; i < node->mNumMeshes; i++)							// Pega os meshes do node e joga no vetor de meshes
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMeshes(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)						// Procula pelos children do node
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMeshes( aiMesh *mesh, const aiScene *scene ) {				// Processa os meshes

	vector<Vertex> vertices; // Vetor de vértices
	vector<unsigned int> indices;  // Vetor de índices
	vector<Texture> textures; // Vetor de texturas

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)						// Cria um novo vértice, passa a informação para ele e coloca no vetor de vértices
	{
		Vertex vertex;															// Declara um novo vertex que segurará as informações do vertice 'i' do mesh

		Vector3 actVertexInformation;											// Quem vai passa as informações pro vértice (que forem vec3)
		
		// Posição
		actVertexInformation.vector[0] = mesh->mVertices[i].x;					// Pega as posições
		actVertexInformation.vector[1] = mesh->mVertices[i].y;
		actVertexInformation.vector[2] = mesh->mVertices[i].z;
		
		vertex.position = actVertexInformation;									// Passa as posições pro vertex

		// Normal
		actVertexInformation.vector[0] = mesh->mNormals[i].x;					// Pega as normals
		actVertexInformation.vector[1] = mesh->mNormals[i].y;
		actVertexInformation.vector[2] = mesh->mNormals[i].z;

		vertex.normal = actVertexInformation;									// Passa as normals pro vertex

		// Textura
		if (mesh->mTextureCoords[0]) {											// Caso o mesh tiver texture coordinates

			Vector2 actTextureInformation;

			actTextureInformation.vector[0] = mesh->mTextureCoords[0][i].x;
			actTextureInformation.vector[1] = mesh->mTextureCoords[0][i].y;

			vertex.textureCoordinates = actTextureInformation;					// Passa as texture coordinates pro vertex
		}
		else {

			Vector2 vec(0.f, 0.f);
			vertex.textureCoordinates = vec;									// Se não tiver texture coordinates deixa tudo como 0
		}

		vertices.push_back(vertex);												// Coloca o vértice no array de structs
	}

	// Indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)							// Para cada número de faces
	{
		aiFace face = mesh->mFaces[i];											// Pega a face atual

		for (unsigned int j = 0; j < face.mNumIndices; j++)						// Para cada índice na face
			indices.push_back(face.mIndices[j]);								// Bota o índice da face no array de índices
	}

	// Materials (se a textura é difusa ou especular)
	if (mesh->mMaterialIndex >= 0) {																				// Se tiver algum material

		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];												// guarda o material

		// Guardar as texturas difusas em um vetor e colocar ele no vetor de texturas (primeiro declarado)
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");		// Retorna um array de texturas do tipo especificado
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());									// e coloca no vetor de texturas dessa função

		// Mesma coisa com o especular
		vector<Texture> specularMaps = loadMaterialTextures( material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);										// Retorna um novo mesh com os dados colocados aqui
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *material, aiTextureType type, string typeName) {

	vector<Texture> textures;														// Vetor de texturas

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)				// Para cada textura com esse tipo
	{
		aiString str;																// Path da textura
		material->GetTexture(type, i, &str);										// Pega o endereço das texturas (o endereço será colocado no str)

		bool alreadyLoaded = false;												    // Vê se a textura já foi carregada

		for (unsigned int j = 0; j < loadedTextures.size(); j++)					// Para cada textura já carregada
		{
			if (std::strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0) {		// Compara se o arquivo é o mesmo, se for

				textures.push_back(loadedTextures[j]);								// Coloca essa textura nos carregados
				alreadyLoaded = true;												// Diz que já está carregado
				break;																// Sai do for para não gastar processamento desnecessário
			}
		}

		if (!alreadyLoaded) {														// Se não estiver sido carregado ainda

			Texture actTexture;														// Cria um struct de textura separado para armazenar os dados
			Texture2D thisTextureID;

			actTexture.ID = thisTextureID.TextureFromFile(str.C_Str(), this->directory,false);		// Carrega a textura especificada (usando o stbi) e retorna o ID dela
			actTexture.type = typeName;												// Armazena p tipo da textura
			actTexture.path = str.C_Str();											// Armazena onde a textura está (foi pego o local no GetTexture)

			textures.push_back(actTexture);											// Coloca essa textura no vetor de texturas
			loadedTextures.push_back(actTexture);
		}
	}
	
	return textures;																// Retorna as texturas
}