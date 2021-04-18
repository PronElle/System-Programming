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
    static std::shared_ptr<Directory> root;
    std::string name;
    std::weak_ptr<Directory> father;
    std::weak_ptr<Directory> _this;
    std::unordered_map<std::string, std::shared_ptr<Base>> children;
    explicit Directory(const std::string &name);

public :
    // overridden methods
    int mType() const override ;
    void ls(int indent) const override;

    static std::shared_ptr<Directory> makeDirectory(std::string name, std::weak_ptr<Directory> parent);
    std::shared_ptr<Directory> addDirectory(const std::string &name);
    static std::shared_ptr<Directory> getRoot();
    std::shared_ptr<File> addFile(const std::string &nome, uintmax_t size);

    // getters
    std::shared_ptr<Base> get(const std::string &name);
    std::shared_ptr<Directory> getDir(const std::string &name);
    std::shared_ptr<File> getFile(const std::string &name);

    bool remove(const std::string &name);
};



#endif //EX2_DIRECTORY_H
