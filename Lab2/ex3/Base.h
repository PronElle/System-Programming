//
// Created by elle on 18/04/21.
//

#ifndef EX2_BASE_H
#define EX2_BASE_H

#include <string>

enum{FILE_t, DIR_t};

class Base {
    std::string name;

public:
    std::string getName() const;
    virtual int mType() const = 0;
    virtual void ls(int indent) const=0;

    explicit Base(const std::string &name);
};


#endif //EX2_BASE_H
