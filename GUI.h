//
// Created by Daniel on 25.04.2022.
//

#ifndef LAB10_GUI_H
#define LAB10_GUI_H

#include "service.h"
#include "GUInotif.h"
#include "GUINotifReadOnly.h"
#include "models.h"

#include "QTIncludes.h"

class GUI : public QWidget{
private:
    Service& service;

    //QListWidget *lst = new QListWidget;
    QTableWidget* table = new QTableWidget(10, 4);
    QTableView *tableview = new QTableView;
    LocatarTableModel *model;

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

    QPushButton *btnNotEdit = new QPushButton("&Editeaza notificari");
    QPushButton *btnNotView = new QPushButton("&Vizualizeaza notificari");

    QPushButton *btnNotAdd = new QPushButton("&Adauga notificare");
    QPushButton *btnNotGen = new QPushButton("&Genereaza notificari");
    QSpinBox *spinBox = new QSpinBox;
    QPushButton *btnNotClear = new QPushButton("&Sterge notificarile");

    QPushButton *btnFilter = new QPushButton("&Filtrare");
    QComboBox *cmbFilter = new QComboBox;

    QPushButton *btnSort = new QPushButton("&Sortare");
    QComboBox *cmbSort = new QComboBox;

    QVBoxLayout *panelButtonsLayout;
    std::vector<QPushButton*> buttons; // suprafete

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
        //p1l->addWidget(lst);
        //p1l->addWidget(table);
        model = new LocatarTableModel;
        model->setElems(service.getLocatari());
        tableview->setModel(model);
        p1l->addWidget(tableview);

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
        notL1->addWidget(btnNotEdit);
        notL1->addWidget(btnNotView);
        auto *notL2 = new QHBoxLayout;
        notL2->addWidget(btnNotAdd);
        notL2->addWidget(btnNotClear);
        auto *notL3 = new QHBoxLayout;
        QLabel* lblgen = new QLabel("Genereaza:");
        notL3->addWidget(lblgen);
        notL3->addWidget(spinBox);
        notL3->addWidget(btnNotGen);
        p2l->addLayout(notL2);
        p2l->addLayout(notL3);
        p2l->addLayout(notL1);
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
        /*int row = 0;
        table->clearContents();
        table->setRowCount(0);
        for(const auto& l : collection)
        {
            auto cell1 = new QTableWidgetItem(std::to_string(l.getApartament()).c_str());
            auto cell2 = new QTableWidgetItem(l.getNumeProprietar().c_str());
            auto cell3 = new QTableWidgetItem(std::to_string(l.getSuprafata()).c_str());
            auto cell4 = new QTableWidgetItem(l.getTip().c_str());
            table->insertRow(row);
            table->setItem(row, 0, cell1);
            table->setItem(row, 1, cell2);
            table->setItem(row, 2, cell3);
            table->setItem(row, 3, cell4);
            row++;
        }*/
        vector<Locatar> rez(collection.begin(), collection.end());
        model->setElems(rez);
    }

    void addButtons()
    {
        for(auto& widget : buttons)
            delete widget;
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
        /*Connect(lst, &QListWidget::itemSelectionChanged, [&](){
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
        });*/
        Connect(table, &QTableWidget::cellClicked, [&](int row, int col){
            int nrap = table->item(row, 0)->text().toInt();
            Locatar l = service.findApartament(nrap);
            Nr->setText(std::to_string(l.getApartament()).c_str());
            Nume->setText(l.getNumeProprietar().c_str());
            Suprafata->setText(std::to_string(l.getSuprafata()).c_str());
            Tip->setText(l.getTip().c_str());
        });
        Connect(tableview->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
            if(tableview->selectionModel()->selectedIndexes().isEmpty())
            {
                Nr->setText("");
                Nume->setText("");
                Suprafata->setText("");
                Tip->setText("");
                return;
            }
            auto selIndex = tableview->selectionModel()->selectedIndexes().at(0);
            int nrap = selIndex.data(Qt::UserRole).toInt();
            const auto& l = service.findApartament(nrap);
            Nr->setText(std::to_string(l.getApartament()).c_str());
            Nume->setText(l.getNumeProprietar().c_str());
            Suprafata->setText(std::to_string(l.getSuprafata()).c_str());
            Tip->setText(l.getTip().c_str());
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
                for(int i=0; i<table->rowCount();++i)
                {
                    int nrap = table->item(i, 0)->text().toInt();
                    if(service.findApartament(nrap) == l) {
                        table->setCurrentCell(i, 0);
                        Nr->setText(std::to_string(l.getApartament()).c_str());
                        Nume->setText(l.getNumeProprietar().c_str());
                        Suprafata->setText(std::to_string(l.getSuprafata()).c_str());
                        Tip->setText(l.getTip().c_str());
                        break;
                    }
                }
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
                //MsgBox(std::to_string(locatari.size()).c_str());
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
        Connect(btnNotEdit, &QPushButton::clicked, [&](){
            GUINotificari* gui = new GUINotificari(service);
            gui->show();
        });
        Connect(btnNotView, &QPushButton::clicked, [&](){
             GUINotifReadOnly* gui = new GUINotifReadOnly(service);
             gui->show();
        });

        Connect(btnNotAdd, &QPushButton::clicked, [&](){
            TypeApartament apartament = Nr->text().toInt();
            try {
                service.addNotificare(apartament);
            }
            catch(MyException& me) { MsgBox(me.what()); }
        });
        Connect(btnNotClear, &QPushButton::clicked, [&](){
            service.clearNotificari();
            MsgBox("Lista de notificari a fost stearsa!");
        });
        Connect(btnNotGen, &QPushButton::clicked, [&](){
            int nr = spinBox->value();
            try{
                service.generateNotificari(nr);
            }
            catch(MyException& me) { MsgBox(me.what());}
        });
    }

public:
    explicit GUI(Service& srv) : service{srv} {
        initGUI();
        loadData(service);
        addButtons();
        init_connect();
    }
};

#endif //LAB10_GUI_H
