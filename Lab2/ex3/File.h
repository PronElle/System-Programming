//
// Created by elle on 18/04/21.
//

#ifndef EX2_FILE_H
#define EX2_FILE_H

#include "Base.h"

class File : public Base{
    uintmax_t size;
public:
    int mType() const;
    uintmax_t getSize() const;
    void ls(int indent) const override;

    File(const std::string &name, uintmax_t size);
};


#endif //EX2_FILE_H
