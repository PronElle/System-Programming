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
std::shared_ptr<Directory> Directory::makeDirectory(const std::string &_name, std::weak_ptr<Directory> parent) {
    auto dir = std::shared_ptr<Directory>(new Directory(_name));
    dir->father = std::move(parent);
    dir->_this = dir;
    return dir;
}

/**
 *
 * @param indent
 */
void Directory::ls(int indent) const {
    std::string indent_str;
    for(int i=0; i<indent; i++)
        indent_str += "\t";

    std::cout<<indent_str<<"[*] "<<getName()<<std::endl;
    for(const auto & element: children)
        element.second->ls(indent+1);
}

/**
 *
 * @param name
 * @return
 */
std::shared_ptr<Directory> Directory::addDirectory(const std::string &_name) {
    if(children.count(_name) > 0 || _name == ".." || _name == ".")
        return std::shared_ptr<Directory>();

    auto dir = makeDirectory(_name, _this);
    children[_name] = dir;
    return dir;
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
std::shared_ptr<File> Directory::addFile(const std::string &_name, uintmax_t size) {
    // if already present
    if(children.count(_name) > 0 || _name == ".." || _name == ".")
        return std::shared_ptr<File>();

    // creating new file
    auto file = std::make_shared<File>(_name, size);
    children[_name] = file;
    return file;
}

/**
 *
 * @param name
 * @return
 */
std::shared_ptr<Base> Directory::get(const std::string &_name) {
    return _name == ".." ?
           father.lock() : _name == "." ?
           _this.lock()  : children.find(_name)->second;
}

/**
 * retrieves dir of given name
 * @param name
 * @return
 */
std::shared_ptr<Directory> Directory::getDir(const std::string &_name) {
    return std::dynamic_pointer_cast<Directory>(get(_name));}

/**
 * retrieves file of given name
 * @param name
 * @return file
 */
std::shared_ptr<File> Directory::getFile(const std::string &_name) {
    return std::dynamic_pointer_cast<File>(get(_name));}

/**
 * deletes children of given name
 * @param name
 * @return true if success, false otherwise
 */
bool Directory::remove(const std::string &_name) {
    return children.erase(_name);
}
