//
// Created by elle on 18/04/21.
//

#include "Base.h"

std::string Base::getName() const {
    return name;
}

Base::Base(const std::string &name) : name(name){}
