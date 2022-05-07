//
// Created by Daniel on 25.04.2022.
//

#ifndef LAB10_GUI_H
#define LAB10_GUI_H

#include "service.h"
#include "GUInotif.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>
#include <qmessagebox.h>
#include <QtWidgets/qcombobox.h>
#include <QTWidgets/qgridlayout.h>

#define Connect QObject::connect
#define MsgBox(msg) QMessageBox::information(this, "Info", msg);
using Locatari = std::vector<Locatar>;

class GUI : public QWidget{
private:
    Service& service;

    QListWidget *lst = new QListWidget;

    QLineEdit *Nr = new QLineEdit;
    QLineEdit *Nume = new QLineEdit;
    QLineEdit *Suprafata = new QLineEdit;
    QLineEdit *Tip = new QLineEdit;
    QLineEdit *Search = new QLineEdit;

    QPushButton *btnAdd = new QPushButton("&Add");
    QPushButton *btnModify = new QPushButton("&Modify");
    QPushButton *btnRemove = new QPushButton("&Remove");
    QPushButton *btnShow = new QPushButton("&Show All");
    QPushButton *btnClear = new QPushButton("&Clear");
    QPushButton *btnSearch = new QPushButton("&Cauta");
    QPushButton *btnUndo = new QPushButton("&Undo");

    QPushButton *btnNotShow = new QPushButton("&Show notificari");

    QPushButton *btnFilter = new QPushButton("&Filtrare");
    QComboBox *cmbFilter = new QComboBox;

    QPushButton *btnSort = new QPushButton("&Sortare");
    QComboBox *cmbSort = new QComboBox;

    QVBoxLayout *panelButtonsLayout;
    std::vector<QPushButton*> buttons; // suprafete

    GUINotificari* guinot;

    // constructor methods
    void initGUI(){
        QHBoxLayout *htable;
        QWidget *panel1, *panel2, *panelbuttons;
        QVBoxLayout *p1l, *p2l;

        // horizontal table
        htable = new QHBoxLayout;
        panel1 = new QWidget;
        panel2 = new QWidget;
        panelbuttons = new QWidget;
        htable->addWidget(panel1);
        htable->addWidget(panel2);
        htable->addWidget(panelbuttons);
        p1l = new QVBoxLayout(panel1);
        p2l = new QVBoxLayout(panel2);
        panelButtonsLayout = new QVBoxLayout(panelbuttons);
        panel1->setLayout(p1l);
        panel2->setLayout(p2l);
        panelbuttons->setLayout(panelButtonsLayout);
        setLayout(htable); /// !

        // panel 1
        p1l->addWidget(lst);
        auto *buttonsL = new QHBoxLayout;
        buttonsL->addWidget(btnRemove);
        buttonsL->addWidget(btnShow);
        p1l->addLayout(buttonsL);
        auto *filterL = new QHBoxLayout;
        filterL->addWidget(btnFilter);
        cmbFilter->addItem("Tip");
        cmbFilter->addItem("Suprafata");
        filterL->addWidget(cmbFilter);
        p1l->addLayout(filterL);
        auto *sortL = new QHBoxLayout;
        sortL->addWidget(btnSort);
        cmbSort->addItem("Nume");
        cmbSort->addItem("Suprafata");
        cmbSort->addItem("Tip + Suprafata");
        sortL->addWidget(cmbSort);
        p1l->addLayout(sortL);

        // panel 2
        auto *card = new QFormLayout;
        card->addRow("Nr Apartament", Nr);
        card->addRow("Nume", Nume);
        card->addRow("Suprafata", Suprafata);
        card->addRow("Tip", Tip);
        p2l->addLayout(card);
        auto *buttonsR = new QHBoxLayout;
        buttonsR->addWidget(btnAdd);
        buttonsR->addWidget(btnModify);
        buttonsR->addWidget(btnUndo);
        buttonsR->addWidget(btnClear);
        p2l->addLayout(buttonsR);
        auto *search = new QHBoxLayout;
        QLabel *srclabel = new QLabel("Cauta/filtreaza");
        search->addWidget(srclabel);
        search->addWidget(Search);
        search->addWidget(btnSearch);
        p2l->addLayout(search);
        p2l->addStretch();

        //notificari
        auto *notL1 = new QHBoxLayout;
        notL1->addWidget(btnNotShow);
        p2l->addLayout(notL1);

        guinot = new GUINotificari(service);
    }

    bool vectorHasSuprafata(int suprafata)
    {
        for(const auto& widget : buttons)
            if(widget->text() == QString::fromStdString(std::to_string(suprafata)))
                return true;
        return false;
    }

    template<class T>
    void loadData(T& collection){
        lst->clear();
        for(const auto& l : collection) {
            lst->addItem(QString::fromStdString(l.toString()));
        }
    }

    void addButtons()
    {
        for(const auto& widget : buttons)
            panelButtonsLayout->removeWidget(widget);
        buttons.clear();
        for(const auto& l : service)
        {
            int supr = l.getSuprafata();
            if(!vectorHasSuprafata(supr))
            {
                QPushButton* btn = new QPushButton(QString::fromStdString(std::to_string(supr)));
                Connect(btn, &QPushButton::clicked, [&, supr](){
                    auto objs = service.filterSuprafata(supr);
                    size_t dim = objs.size();
                    MsgBox(QString::fromStdString("Numarul de apartamente cu aceasta suprafata este: "+std::to_string(dim)));
                });
                panelButtonsLayout->addWidget(btn);
                buttons.push_back(btn);
            }
        }
    }

    void init_connect(){
        //butoane helper
        Connect(btnShow, &QPushButton::clicked, [&](){loadData(service); addButtons();});
        Connect(btnClear, &QPushButton::clicked, [&](){
            Nr->setText("");
            Nume->setText("");
            Suprafata->setText("");
            Tip->setText("");
        });
        // lista
        Connect(lst, &QListWidget::itemSelectionChanged, [&](){
            if (lst->selectedItems().isEmpty()) {
                //daca nu e nimic selectat golesc campurile
                btnClear->animateClick();
                return;
            }
            auto *currentItem = lst->selectedItems().at(0);
            Locatar locatar = Locatar::fromString(currentItem->text().toStdString());
            Nr->setText(QString::fromStdString(std::to_string(locatar.getApartament())));
            Nume->setText(QString::fromStdString(locatar.getNumeProprietar()));
            Suprafata->setText(QString::fromStdString(std::to_string(locatar.getSuprafata())));
            Tip->setText(QString::fromStdString(locatar.getTip()));
        });

        //butoane CRUD
        Connect(btnAdd, &QPushButton::clicked, [&](){
            auto numar = Nr->text().toInt();
            auto nume = Nume->text().toStdString();
            auto sup = Suprafata->text().toInt();
            auto tip = Tip->text().toStdString();
            try {
                service.add(numar, nume, sup, tip);
                loadData(service); addButtons();
            }
            catch(MyException& me) { MsgBox(me.what()); }
        });
        Connect(btnRemove, &QPushButton::clicked, [&](){
            auto numar = Nr->text().toInt();
            auto nume = Nume->text().toStdString();
            auto sup = Suprafata->text().toInt();
            auto tip = Tip->text().toStdString();
            try {
                service.remove(numar, nume, sup, tip);
                loadData(service); addButtons();
            }
            catch(MyException& me) { MsgBox(me.what()); }
        });
        Connect(btnModify, &QPushButton::clicked, [&](){
            auto numar = Nr->text().toInt();
            auto nume = Nume->text().toStdString();
            auto sup = Suprafata->text().toInt();
            auto tip = Tip->text().toStdString();
            try {
                service.modify(numar, numar, nume, sup, tip);
                loadData(service); addButtons();
            }
            catch(MyException& me) { MsgBox(me.what()); }
        });
        Connect(btnSearch, &QPushButton::clicked, [&](){
            auto text = Search->text().toInt();
            try{
                Locatar l = service.findApartament(text);
                for(int i=0; i<lst->count();++i)
                    if(lst->item(i)->text().toStdString() == l.toString())
                        lst->setCurrentRow(i);
            }
            catch(MyException& me) { MsgBox(me.what()); }
        });

        //filter sort undo
        Connect(btnFilter, &QPushButton::clicked, [&](){
            auto text = Search->text();
            if(cmbFilter->currentText() == "Tip")
            {
                Locatari locatari = service.filterTip(text.toStdString());
                loadData(locatari);
            }
            else if(cmbFilter->currentText() == "Suprafata")
            {
                Locatari locatari = service.filterSuprafata(text.toInt());
                loadData(locatari);
            }
        });
        Connect(btnSort, &QPushButton::clicked, [&](){
            if(cmbSort->currentText() == "Nume")
            {
                service.sortNume();
                loadData(service);
            }
            else if(cmbSort->currentText() == "Suprafata")
            {
                service.sortSuprafata();
                loadData(service);
            }
            else if(cmbSort->currentText() == "Tip + Suprafata")
            {
                service.sortTipSuprafata();
                loadData(service);
            }
        });
        Connect(btnUndo, &QPushButton::clicked, [&](){
            try{
                service.undo();
                loadData(service); addButtons();
            }
            catch(MyException& me) {QMessageBox::information(this, "Eroare", me.what());}
        });

        //notificari
        Connect(btnNotShow, &QPushButton::clicked, [&](){
            guinot->show();
        });
    }

public:
    explicit GUI(Service& srv) : service{srv} {
        initGUI();
        loadData(service); addButtons();
        init_connect();
    }
};

#endif //LAB10_GUI_H
