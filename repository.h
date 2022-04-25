#ifndef LAB6_REPOSITORY_H
#define LAB6_REPOSITORY_H

#include <type_traits>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "exceptions.h"
using std::vector;
using std::ifstream;
using std::ofstream;

template<typename T>
class Repository{
protected:
    vector<T> elements;
    typename vector<T>::iterator getIterator(T* pointer) { return elements.begin() + (pointer - elements.data()); }
public:
    Repository() = default;

    // operator de atribuire
    // Repository& operator=(const Repository&);

    // indexator, returnez o referinta la obiect
    // arunc RepoException daca pozitia este invalida
    T& operator[](const int& index)
    {
        try{ return elements[index]; }
        catch(...) { throw RepoException("Indexul "+std::to_string(index)+" este invalid!\n");}
    }


    // returneaza numarul de elemente continute
    int size() const {return elements.size(); }

    // adaug un element la finalul containerului
    // arunc RepoException daca elementul se afla in container
    virtual void add(const T & element) {
        const T* it = find(element);
        if(it != NULL) throw RepoException("Element duplicat!\n");
        elements.push_back(element);
    }

    // returnez o referinta catre primul element egal cu cel dat
    // sau NULL altfel
    // primul iterator indica pozitia de inceput
    // al doilea indica pozitia de final
    // implicit, cautarea de face pe tot containerul
    T* find(const T & element, T* begin = NULL, T* end = NULL) {
        if(begin == NULL) begin = this->begin();
        if(end == NULL) end = this->end();
        for(auto it=begin; it != end; ++it)
            if(*it == element)
                return it;
        return NULL;
    }

    // returnez un iterator catre primul element care respecta proprietatea data
    // daca elementul nu este gasit, returnez NULL
    // primul iterator indica pozitia de inceput
    // al doilea indica pozitia de final
    // implicit, cautarea de face pe tot containerul
    template<class UnaryPredicate>
    T* find(UnaryPredicate fct, T* begin = NULL, T* end = NULL) {
        if(begin == NULL) begin = this->begin();
        if(end == NULL) end = this->end();
        for(auto it=begin; it != end; ++it)
            if(fct(*it))
                return it;
        return NULL;
    }

    // sterg prima aparitie a elementului dat din container
    // arunc o exceptie daca nu exista in container
    virtual void remove(const T& element) {
        T* it = find(element);
        if(it == NULL) throw RepoException("Elementul inexistent!\n");

        elements.erase(getIterator(it));
    }

    // sterg primul element care respecta proprietatea
    // returnez elementul sters
    // arunc o exceptie daca nu exista in container
    template<class UnaryPredicate>
    T remove(UnaryPredicate fct) {
        T* it = find(fct);
        if(it == NULL) throw RepoException("Elementul inexistent!\n");
        elements.erase(getIterator(it));
        return *it;
    }

    // modific valoarea elementului 1 in elementul 2
    // arunc repoexception daca element1 nu exista in repo
    virtual void modify(const T& element1, const T& element2)
    {
        bool gasit = false;
        for(auto& elem : elements)
            if(elem == element1)
                elem = element2,
                gasit = true;
        if(!gasit) throw RepoException("Elementul nu exista!\n");
    }

    // sortez repository-ul dupa operatorul < sau dupa functie
    template<class Compare=std::less<T>>
    void sort(Compare compare = Compare{}){
        std::sort(elements.begin(), elements.end(), compare);
    }

    // implementez iteratorii de begin si end pentru a putea intera
    T* begin() { return elements.begin().base();}
    const T* cbegin() const {return elements.cbegin().base(); }
    T* end() {return elements.end().base(); }
    const T* cend() const {return elements.cend().base(); }

    virtual ~Repository() = default;
};

template<typename T>
class FileRepository : public Repository<T>{
private:
    string path;
    void fromFile(){ // iau datele din fisier
        ifstream fin(path);
        if(!fin.is_open()) throw RepoException("Eroare la deschiderea fisierului"+path+"!");
        Locatar l;
        while(!fin.eof())
        {
            fin>>l;
            if(fin.eof()) break;
            Repository<T>::add(l);
        }
        fin.close();
    }
    void toFile(){
        ofstream fout(path);
        if(!fout.is_open()) throw RepoException("Eroare la deschiderea fisierului"+path+"!");
        for(const auto& elem : Repository<T>::elements)
            fout<<elem<<'\n';
        fout.close();
    }
public:
    explicit FileRepository(const string& path) : Repository<T>(), path(path) { fromFile(); }
    void add(const T & element) override{
        Repository<T>::add(element);
        toFile();
    }
    void remove(const T& element) override{
        Repository<T>::remove(element);
        toFile();
    }
};

#endif //LAB6_REPOSITORY_H
