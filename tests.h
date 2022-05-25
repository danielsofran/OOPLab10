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
#include "observer.h"

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

class TestObserver : public Observer{
public:
    int val = 0;
    void update() override{
        val = 1;
    }
};

class TestObservable : public Observable{
public:
    TestObservable(){
        TestObserver o[4];
        for(auto & i : o)
            addObserver(&i);
        notify();
        for(auto & i : o)
            assert(i.val == 1);
    }
};

void test();

#endif // LAB6_TESTS_H
