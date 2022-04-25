//
// Created by Daniel on 26.03.2022.
//

#include "validator.h"

void ValidatorLocatar::validApartament(const TypeApartament & apartament) {
    if(apartament > 0 && apartament < 1000);
    else throw InvalidFieldException("Apartamentul "+std::to_string(apartament)+" este invalid!\n");
}

void ValidatorLocatar::validNume(const TypeNume & nume) {
    for(int i=0;i<nume.size();++i)
        if(!std::isalpha(nume[i]) && !std::isblank(nume[i]))
            throw InvalidFieldException("Numele proprietarului "+nume+" nu este valid!\n");
}

void ValidatorLocatar::validSuprafata(const TypeSuprafata & suprafata) {
    if(suprafata > 0 && suprafata < 10000);
    else throw InvalidFieldException("Suprafata "+std::to_string(suprafata)+" nu este valida!\n");
}

void ValidatorLocatar::validTip(const TypeTip & tip) {
    for(int i=0;i<tip.size();++i)
        if(!std::isalnum(tip[i]) && !std::isblank(tip[i]))
            throw InvalidFieldException("Tipul "+tip+" nu este valid!\n");
}

void ValidatorLocatar::validLocatar(const Locatar & locatar) {
    ValidatorException v;
    try{ validApartament(locatar.getApartament()); }
    catch(InvalidFieldException& ie) {v += ie;}
    try{ validNume(locatar.getNumeProprietar()); }
    catch(InvalidFieldException& ie) {v += ie;}
    try{ validSuprafata(locatar.getSuprafata());}
    catch(InvalidFieldException& ie) {v += ie;}
    try { validTip(locatar.getTip()); }
    catch(InvalidFieldException& ie) {v += ie;}
    if((int)v != 0) throw ValidatorException(v);
}
