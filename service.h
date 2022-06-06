//
// Created by Daniel on 26.03.2022.
//

#ifndef LAB6_SERVICE_H
#define LAB6_SERVICE_H

#include <fstream>
#include <regex>
#include <random>
#include <algorithm>
#include <chrono>
#include <set>
#include <map>

#include "domain.h"
#include "repository.h"
#include "validator.h"
#include "observer.h"

using std::vector;
using std::map;

class ActiuneUndo{
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo(){};
};

class UndoAdauga : public ActiuneUndo{
    Locatar locatar;
    Repository<Locatar>& repo;
public:
    UndoAdauga(Repository<Locatar>& rep, const Locatar& l) : repo{rep}, locatar{l}{}
    void doUndo() override { repo.remove(locatar); }
};

class UndoSterge : public ActiuneUndo{
    Locatar locatar;
    Repository<Locatar>& repo;
public:
    UndoSterge(Repository<Locatar>& rep, const Locatar& l) : repo{rep}, locatar{l}{}
    void doUndo() override{ repo.add(locatar); }
};

class UndoModifica : public ActiuneUndo{
    Locatar locatar1, locatar2;
    Repository<Locatar>& repo;
public:
    UndoModifica(Repository<Locatar>& rep, const Locatar& l1, const Locatar& l2) : repo{rep}, locatar1{l1}, locatar2{l2} {}
    void doUndo() override{ repo.modify(locatar2, locatar1); }
};



class Service : public Observable{
    friend class TestService;
private:
    Repository<Locatar>& repository;
    vector<Locatar> listanotificare;
    vector<std::unique_ptr<ActiuneUndo>> undos;
public:
    // doar constructor cu param repo
    explicit Service(Repository<Locatar>& repo) : repository{repo} {};
    Service(const Service&) = delete;

    // adauga elementul in repository
    // arunca ServiceException daca nu a putut fi creat
    // arunca RepoException daca exista in container
    // arunca ValidatorException daca nu este valid
    void add(const TypeApartament&, const TypeNume&, const TypeSuprafata&, const TypeTip&);

    // sterge elementul din repository
    // arunca RepoException daca elementul nu exista
    // arunca ValidatorException daca nu este valid
    void remove(const TypeApartament&, const TypeNume&, const TypeSuprafata&, const TypeTip&);

    // modific primul elemet cu al doilea
    // arunca RepoException daca elementul nu exista
    // arunca ValidatorException daca unul din locatari nu este valid
    void modify(const TypeApartament&, const TypeApartament&, const TypeNume&, const TypeSuprafata&, const TypeTip&);

    // cauta apartamentul cu numarul dat
    // arunca ServiceException daca nu exista un astfel de apartament
    // arunca InvalidFieldException daca nu este valid
    const Locatar& findApartament(const TypeApartament&);

    // returnez toate elementele care au tipul dat
    // arunca InvalidFieldException daca nu este valid
    vector<Locatar> filterTip(const TypeTip&);

    // returnez toate elementele care au suprafata data?
    // arunca InvalidFieldException daca nu este valid
    vector<Locatar> filterSuprafata(const TypeSuprafata&);

    // sortez repository-ul dupa nume crescator
    void sortNume();

    // sortez repository-ul dupa suprafata crescator
    void sortSuprafata();

    // sortez repository-ul dupa tip, iar la tipuri egale sortez dupa suprafata
    void sortTipSuprafata();

    // returnez un dictionar in care cheia este apartamentul iar valoarea este numarul sau de aparitii
    map<TypeApartament, int> raportApartamente();

    // refac ultima adaugare/stergere/modificare
    // arunc ServiceException daca nu exista operatii ce pot fi refacute
    void undo();

    // adaug apartamentul cu nr dat in lista de notificare
    // arunc ServiceException daca nu exista
    void addNotificare(const int&);

    // sterg lista de notificari
    void clearNotificari();

    // adaug n apartamente alese aleator
    void generateNotificari(const int&);

    // export ca fisier HTML
    void exportNotificariHTML(const string&);

    // export ca fisier CSV
    void exportNotificariCSV(const string&);

    // implementare iteratori de begin si end pentru a putea intera
    Locatar* begin();
    const Locatar* cbegin() const;
    Locatar* end();
    const Locatar* cend() const;

    // lista de notificari
    const vector<Locatar>& getNotificari();

    vector<Locatar> getLocatari();
};

#endif //LAB6_SERVICE_H
