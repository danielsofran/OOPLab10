//
// Created by Daniel on 26.03.2022.
//

#ifndef LAB6_VALIDATOR_H
#define LAB6_VALIDATOR_H

#include <cctype>
#include "domain.h"
#include "exceptions.h"

class ValidatorLocatar{
public:
    // validatori campuri
    // arunca InvalidFieldException daca valorile nu sunt valide
    static void validApartament(const TypeApartament&);
    static void validNume(const TypeNume&);
    static void validSuprafata(const TypeSuprafata&);
    static void validTip(const TypeTip&);

    // validator locatar
    // arunca ValidatorException continand fiecare eroare de validare a fiecarui camp
    static void validLocatar(const Locatar&);
};

#endif //LAB6_VALIDATOR_H
