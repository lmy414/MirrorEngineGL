#ifndef MODELPOOL_H
#define MODELPOOL_H

#include <unordered_map>
#include <memory>
#include "Model.h"

class ModelPool {
public:

    // 获取模型池中的所有模型
    const std::unordered_map<GLuint, std::shared_ptr<Model>>& GetModels() const {
        std::cout << "Getting all models from the pool." << std::endl;  // 调试信息
        return m_models;
    }

    // 单例模式
    static ModelPool& Instance() {
        static ModelPool instance;
        std::cout << "ModelPool instance created." << std::endl;  // 调试信息
        return instance;
    }

    // 添加模型到模型池
    void AddModel(const std::shared_ptr<Model>& model) {
        std::cout << "Adding model to pool: " << model->GetName() << std::endl;  // 调试信息
        m_models[model->GetID()] = model;
    }

    // 通过ID获取模型
    std::shared_ptr<Model> GetModelByID(GLuint id) {
        std::cout << "Fetching model by ID: " << id << std::endl;  // 调试信息
        if (m_models.find(id) != m_models.end()) {
            return m_models[id];
        }
        std::cout << "Model with ID " << id << " not found!" << std::endl;  // 调试信息
        return nullptr;
    }

    // 通过名称获取模型
    std::shared_ptr<Model> GetModelByName(const std::string& name) {
        std::cout << "Fetching model by name: " << name << std::endl;  // 调试信息
        for (const auto& pair : m_models) {
            if (pair.second->GetName() == name) {
                std::cout << "Model found by name: " << name << std::endl;  // 调试信息
                return pair.second;
            }
        }
        std::cout << "Model with name " << name << " not found!" << std::endl;  // 调试信息
        return nullptr;
    }

    // 检查模型是否已加载
    bool ModelExists(const std::string& name) {
        bool exists = GetModelByName(name) != nullptr;
        std::cout << "Model exists check for " << name << ": " << (exists ? "Yes" : "No") << std::endl;  // 调试信息
        return exists;
    }

    // 加载模型，如果模型已存在则返回已加载的模型
    std::shared_ptr<Model> LoadModel(const std::string& name, const std::string& path) {
        std::cout << "Loading model: " << name << " from path: " << path << std::endl;  // 调试信息
        if (ModelExists(name)) {
            std::cout << "Model already loaded: " << name << std::endl;  // 调试信息
            return GetModelByName(name); // 如果模型已加载，直接返回
        }

        // 如果模型未加载，创建新的模型并加载
        std::shared_ptr<Model> newModel = std::make_shared<Model>(name, path);
        AddModel(newModel);  // 添加到模型池中
        std::cout << "New model added: " << name << std::endl;  // 调试信息
        return newModel;
    }

    // 移除模型（根据模型ID）
    void RemoveModelByID(GLuint id) {
        std::cout << "Removing model by ID: " << id << std::endl;  // 调试信息
        if (m_models.find(id) != m_models.end()) {
            m_models.erase(id);
            std::cout << "Model removed by ID: " << id << std::endl;  // 调试信息
        } else {
            std::cout << "Model ID not found: " << id << std::endl;  // 调试信息
        }
    }

    // 移除模型（根据模型名称）
    void RemoveModelByName(const std::string& name) {
        std::cout << "Removing model by name: " << name << std::endl;  // 调试信息
        auto it = m_models.begin();
        while (it != m_models.end()) {
            if (it->second->GetName() == name) {
                m_models.erase(it);
                std::cout << "Model removed by name: " << name << std::endl;  // 调试信息
                return;
            }
            ++it;
        }
        std::cout << "Model name not found: " << name << std::endl;  // 调试信息
    }

    // 移除所有模型
    void RemoveAllModels() {
        std::cout << "Removing all models from the pool." << std::endl;  // 调试信息
        m_models.clear();
        std::cout << "All models have been removed from the pool." << std::endl;  // 调试信息
    }

private:
    std::unordered_map<GLuint, std::shared_ptr<Model>> m_models; // 通过ID查找模型
};

#endif // MODELPOOL_H
