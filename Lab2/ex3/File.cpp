//
// Created by elle on 18/04/21.
//

#include "File.h"
#include  <iostream>

int File::mType() const {
    return FILE_t;
}

uintmax_t File::getSize() const {
    return size;
}

void File::ls(int indent) const {
    std::string str;

    for(int i = 0; i < indent; ++i)
        str += "\t";

    std::cout << str << getName() << " " << size << "\n";
}

File::File(const std::string &name, uintmax_t size)
        : Base(name), size(size) {}

