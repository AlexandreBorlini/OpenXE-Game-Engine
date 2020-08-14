#include "glew.h"
#include "Mesh.h"
#include "Shader.h"
#include "Render/Texture2D.h"

#include "Math/Vector3.h"
#include "Math/Vector2.h"

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#include "FrameBuffer.h"
#include "Camera.h"
#include "Transform.h"

class Model
{
public:

	Transform transform;

	Model(const GLchar *path, const char *shaderType);

	void use(Camera camera, Vector3 lightPos);   // Renderizar o model
	void shadedUse(Camera camera, Camera lightCamera, FrameBuffer depthMap, Vector3 lightPos);

	void useModel(Camera camera); // Renderiza apenas o model !usar em sombras
	void onlyDraw();

	void changeDiffuseValue(float value)   { objDiffuseValue = value;   }
	void changeSpecularValue(float value)  { objSpecluarValue = value;  }
	void changeAmbientValue(float value)   { objAmbientValue = value;   }
	void changeShininessValue(float value) { objShininessValue = value; }

private:
	
	float objDiffuseValue = .7f;
	float objSpecluarValue = .35f;
	float objAmbientValue = 0.2f;
	float objShininessValue = 64.f;

	Shader shader;

	vector<Texture> loadedTextures;		     // Texturas que já foram carregadas
	vector<Mesh> meshes;					 // Vetor dos meshes do modelo
	string directory;

	void loadModel(string path);			// Carregar o modelo

	void processNode( aiNode *node, const aiScene *scene );		// Processar o node
	Mesh processMeshes( aiMesh *mesh, const aiScene *scene );	// Processar o Mesh do node

	vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, string typeName);
};