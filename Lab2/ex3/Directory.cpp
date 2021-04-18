//
// Created by elle on 17/04/21.
//

#include "Directory.h"

std::shared_ptr<Directory> Directory::root; // dir's root

Directory::Directory(const std::string &name) : Base(name) {}

/**
 * retrieves the type of instance (File/Dir)
 * @return type
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
 * Unix-like "ls" command
 * @param indentation level
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
 * Creates a new object of type Directory
 * and adds it to the current dir
 * @param name
 * @return new dir or empty shared ptr
 */
std::shared_ptr<Directory> Directory::addDirectory(const std::string &_name) {
    if(children.count(_name) > 0 || _name == ".." || _name == ".")
        return std::shared_ptr<Directory>();

    auto dir = makeDirectory(_name, _this);
    children[_name] = dir;
    return dir;
}

/**
 * Creates root of dir's tree or retrives it if
 * already present
 * @return root
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
 * Creates a new object of type File
 * and adds it to the current dir
 * @param _name
 * @param size
 * @return new file
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
 * Retrives a smart pointer of Dir/File with appropriate name
 * under current directory
 * @param _name
 * @return
 */
std::shared_ptr<Base> Directory::get(const std::string &_name) {
    return _name == ".." ?
           father.lock() : _name == "." ?
           _this.lock()  : children.find(_name)->second;
}

/**
 * retrieves dir of given name employing "get" method
 * @param _name
 * @return dir
 */
std::shared_ptr<Directory> Directory::getDir(const std::string &_name) {
    return std::dynamic_pointer_cast<Directory>(get(_name));}

/**
 * retrieves file of given name
 * @param _name
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
