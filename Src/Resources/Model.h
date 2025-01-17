#ifndef MODEL_H
#define MODEL_H

#include <assimp/scene.h>
#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include "Texture.h"
#include "../Render/Mesh.h"

class Model {
public:
    // 已加载纹理，避免重复加载
    std::vector<Texture2D*> textures_loaded;  
    // 网格列表
    std::vector<Mesh*> meshes;  
    // 模型文件所在目录
    std::string directory;  
    // 模型文件路径
    std::string mesh_path;  
    // 伽马校正标记
    bool gammaCorrection;  
    // 模型名称
    std::string name;  

    // 静态存储已加载模型
    static std::map<std::string, Model*> LoadedModel;

    // 编辑器资源，引用场景模型
    //EditorResource<SceneModel*> refSceneModels; 

    // 构造函数，接受文件路径和伽马校正标记
    Model(std::string const &path, bool gamma = false);
    //Model(std::filesystem::path path, bool gamma = false);
    Model() : gammaCorrection(false), mesh_path("") {}//默认的构造函数

    // 析构函数，释放资源
    ~Model();
    
private:
    // 加载模型数据
    void loadModel();
    
    // 递归处理节点，加载网格
    void processNode(aiNode* node, const aiScene* scene);
    
    // 处理单个网格
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    
    // 加载材质纹理
    std::vector<Texture2D*> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
};

#endif
