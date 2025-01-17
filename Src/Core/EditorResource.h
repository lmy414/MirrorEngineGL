#pragma once
#include <vector>



template <class T>
class EditorResource
{
public:
    std::vector<T> references;  // 存储 T 类型的指针

    void AddRef(T ref_target) { references.push_back(ref_target); }

    void RemoveRef(T remove_target) { 
        references.erase(remove(references.begin(), references.end(), remove_target), references.end()); 
    }
};
