//
// Created by elle on 17/04/21.
//

#ifndef EX2_DIRECTORY_H
#define EX2_DIRECTORY_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include "Base.h"
#include "File.h"

class Directory : public Base {
    std::string name;
    std::weak_ptr<Directory> father;
    std::weak_ptr<Directory> _this;
    std::unordered_map<std::string, std::shared_ptr<Base>> children;
    Directory(const std::string &name);

public :
    int mType() const;
    static std::shared_ptr<Directory> makeDirectory(std::string name, std::weak_ptr<Directory> parent);
    void ls(int indent) const;
    std::shared_ptr<Directory> addDirectory(const std::string &nome);
    static std::shared_ptr<Directory> getRoot();
    std::shared_ptr<File> addFile(const std::string &nome, uintmax_t size);
    std::shared_ptr<Base> get(const std::string &name);
    std::shared_ptr<Directory> getDir(const std::string &name);
    std::shared_ptr<File> getFile(const std::string &name);
    bool remove(const std::string &nome);
};



#endif //EX2_DIRECTORY_H
