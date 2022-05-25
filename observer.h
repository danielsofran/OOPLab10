//
// Created by Daniel on 25.05.2022.
//

#ifndef LAB10_OBSERVER_H
#define LAB10_OBSERVER_H

#include "vector"
#include "algorithm"
#include "exceptions.h"
using std::vector;

class Observer{
public:
    virtual void update() = 0;
};

class Observable{
private:
    vector<Observer*> observers;
public:
    void addObserver(Observer* obs)
    {
        observers.push_back(obs);
    }
    void removeObserver(Observer* obs)
    {
        auto it = std::find(observers.begin(), observers.end(), obs);
        if(it == observers.end()) throw NoObserverException("Elementul nu exista in lista de notificatii");
        observers.erase(it);
    }

protected:
    void notify(){
        for(auto& obs : observers)
            obs->update();
    }
};

#endif //LAB10_OBSERVER_H
