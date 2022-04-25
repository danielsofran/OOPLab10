//
// Created by Daniel on 25.03.2022.
//

#include "domain.h"

Locatar::Locatar(const Locatar & obj) {
    apartament = obj.apartament;
    nume_proprietar = obj.nume_proprietar;
    suprafata = obj.suprafata;
    tip = obj.tip;
    //std::cout<<"Obiectul "<<obj<<"\n a fost copiat!\n";
}

Locatar& Locatar::operator=(const Locatar& obj){
    apartament = obj.apartament;
    nume_proprietar = obj.nume_proprietar;
    suprafata = obj.suprafata;
    tip = obj.tip;
    return *this;
}

TypeApartament Locatar::getApartament() const { return apartament; }
TypeNume Locatar::getNumeProprietar() const { return nume_proprietar; }
TypeSuprafata Locatar::getSuprafata() const { return suprafata; }
TypeTip Locatar::getTip() const { return tip; }

void Locatar::setApartament(const TypeApartament& value) { apartament = value; }
void Locatar::setNumeProprietar(const TypeNume& value) { nume_proprietar = value; }
void Locatar::setSuprafata(const TypeSuprafata& value) { suprafata = value; }
void Locatar::setTip(const TypeTip& value) { tip = value; }

bool Locatar::operator==(const Locatar & obj) const {
    return  apartament == obj.apartament &&
            nume_proprietar == obj.nume_proprietar &&
            suprafata == obj.suprafata &&
            tip == obj.tip;
}
bool Locatar::operator!=(const Locatar & obj) const { return !(*this == obj); }

bool Locatar::operator<(const Locatar & obj) const { return this->apartament < obj.apartament; }
bool Locatar::operator>(const Locatar & obj) const { return !(*this<obj) && !(*this == obj);}
bool Locatar::operator<=(const Locatar & obj) const { return !(*this > obj); }
bool Locatar::operator>=(const Locatar &obj) const { return !(*this < obj); }

istream & operator>>(istream& in, Locatar& obj)
{
    //bool consoleMSG = false;
    //if(consoleMSG) std::cout<<"Apartament: ";
    in>>obj.apartament;
    //if(consoleMSG) std::cout<<"Nume Proprietar: ";
    in>>obj.nume_proprietar;
    //if(consoleMSG) std::cout<<"Suprafata: ";
    in>>obj.suprafata;
    //if(consoleMSG) std::cout<<"Tip: ";
    in>>obj.tip;
    return in;
}

ostream& operator<<(ostream& out, const Locatar& obj){
    out<<obj.apartament<<' '<<obj.nume_proprietar<<' '<<obj.suprafata<<' '<<obj.tip;
    return out;
}

string Locatar::toString() const {
    std::ostringstream out;
    out<<std::setw(3)<<apartament<<' ';
    out<<std::setw(15)<<nume_proprietar<<' ';
    out<<std::setw(7)<<suprafata<<' ';
    out<<std::setw(15)<<tip<<' ';
    return string(out.str());
}

Locatar Locatar::fromString(const string& txt) {
    std::istringstream in(txt);
    Locatar rez;
    in>>rez;
    return rez;
}