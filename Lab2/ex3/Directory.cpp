//
// Created by elle on 17/04/21.
//

#include "Directory.h"

std::shared_ptr<Directory> Directory::root; // dir's root

Directory::Directory(const std::string &name) : Base(name) {}

/**
 *
 * @return
 */
int Directory::mType() const {
    return DIR_t;
}

/**
 *
 * @param name
 * @param parent
 * @return
 */
std::shared_ptr<Directory> Directory::makeDirectory(std::string name, std::weak_ptr<Directory> parent) {
    return std::shared_ptr<Directory>();
}

/**
 *
 * @param indent
 */
void Directory::ls(int indent) const {

}

/**
 *
 * @param name
 * @return
 */
std::shared_ptr<Directory> Directory::addDirectory(const std::string &name) {
    return std::shared_ptr<Directory>();
}

/**
 *
 * @return
 */
std::shared_ptr<Directory> Directory::getRoot() {
    if(root == nullptr){
        root = std::shared_ptr<Directory>(new Directory("/"));
        root->_this = root;
        root->father = root;
    }

    return root;
}

/**
 *
 * @param nome
 * @param size
 * @return
 */
std::shared_ptr<File> Directory::addFile(const std::string &nome, uintmax_t size) {
    return std::shared_ptr<File>();
}

/**
 *
 * @param name
 * @return
 */
std::shared_ptr<Base> Directory::get(const std::string &name) {
    return name == ".." ?
           father.lock() : name == "." ?
           _this.lock()  : children.find(name)->second;
}

/**
 * retrieves dir of given name
 * @param name
 * @return
 */
std::shared_ptr<Directory> Directory::getDir(const std::string &name) {
    return std::dynamic_pointer_cast<Directory>(get(name));}

/**
 * retrieves file of given name
 * @param name
 * @return file
 */
std::shared_ptr<File> Directory::getFile(const std::string &name) {
    return std::dynamic_pointer_cast<File>(get(name));}

/**
 * deletes children of given name
 * @param name
 * @return true if success, false otherwise
 */
bool Directory::remove(const std::string &name) {
    return children.erase(name);
}
