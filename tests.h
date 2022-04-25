//
// Created by Daniel on 25.03.2022.
//

#ifndef LAB6_TESTS_H
#define LAB6_TESTS_H

#include <cassert>
#include <cstring>
#include <strstream>
#include "exceptions.h"
#include "domain.h"
#include "validator.h"
#include "repository.h"
#include "service.h"

class ITest{
protected:
    virtual void ctors(){}
    virtual void getters(){}
    virtual void setters(){}
    virtual void operators(){}
    virtual void methods(){}
    virtual void add(){}
    virtual void find(){}
    virtual void remove(){}
    virtual void filter(){}
    virtual void sort(){}

public:
    void run(){
        ctors();
        getters();
        setters();
        methods();
        operators();
        add();
        remove();
        find();
        filter();
        sort();
    }
    ITest()=default;
};

void test();

#endif // LAB6_TESTS_H
