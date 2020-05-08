#include "glew.h"
#include "Mesh.h"
#include "Shader.h"
#include "Render/Texture2D.h"

#include "Math/Vector3.h"
#include "Math/Vector2.h"

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#include "Camera.h"
#include "Transform.h"

class Model
{
public:

	Transform transform;

	Model(const GLchar *path) { loadModel(path);
								Shader newShader("bookVertexShader.vs", "bookFragmentShader.fs");
								shader = newShader; }
	
	void use(Camera camera);   // Renderizar o model

private:

	Shader shader;

	vector<Texture> loadedTextures;		     // Texturas que já foram carregadas
	vector<Mesh> meshes;					// Vetor dos meshes do modelo
	string directory;

	void loadModel(string path);			// Carregar o modelo

	void processNode( aiNode *node, const aiScene *scene );		// Processar o node
	Mesh processMeshes( aiMesh *mesh, const aiScene *scene );	// Processar o Mesh do node

	vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, string typeName);
};
