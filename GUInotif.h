//
// Created by Daniel on 06.05.2022.
//

#ifndef LAB10_GUINOTIF_H
#define LAB10_GUINOTIF_H

#include "service.h"
#include "observer.h"
#include "QTIncludes.h"

class GUINotificari : public QWidget, public Observer{
private:
    Service& service;

    QListWidget *lst = new QListWidget;

    QLineEdit *Nr = new QLineEdit;
    QLineEdit *Nume = new QLineEdit;
    QLineEdit *Suprafata = new QLineEdit;
    QLineEdit *Tip = new QLineEdit;

    QPushButton *btnNotShow = new QPushButton("&Show notificari");
    QPushButton *btnNotAdd = new QPushButton("&Adauga notificare");
    QPushButton *btnNotGen = new QPushButton("&Genereaza notificari");
    QSpinBox *spinBox = new QSpinBox;
    QPushButton *btnNotClear = new QPushButton("&Sterge notificarile");
    QPushButton *btnNotExportHTML = new QPushButton("&Exporta HTML");
    QPushButton *btnNotExportCSV = new QPushButton("&Exporta CSV");
    QLineEdit *Path = new QLineEdit;

    // constructor methods
    void initGUI(){
        QHBoxLayout *htable;
        QWidget *panel1, *panel2;
        QVBoxLayout *p1l, *p2l;

        // horizontal table
        htable = new QHBoxLayout;
        panel1 = new QWidget;
        panel2 = new QWidget;
        htable->addWidget(panel1);
        htable->addWidget(panel2);
        p1l = new QVBoxLayout(panel1);
        p2l = new QVBoxLayout(panel2);
        panel1->setLayout(p1l);
        panel2->setLayout(p2l);
        setLayout(htable); /// !

        // panel 1
        p1l->addWidget(lst);

        // panel 2
        auto *card = new QFormLayout;
        card->addRow("Nr Apartament", Nr);
        card->addRow("Nume", Nume);
        card->addRow("Suprafata", Suprafata);
        card->addRow("Tip", Tip);
        p2l->addLayout(card);
        p2l->addStretch();

        //notificari
        auto *notL1 = new QHBoxLayout;
        notL1->addWidget(btnNotShow);
        notL1->addWidget(btnNotAdd);
        notL1->addWidget(btnNotClear);
        p2l->addLayout(notL1);
        auto *notL2 = new QHBoxLayout;
        notL2->addWidget(btnNotGen);
        notL2->addWidget(spinBox);
        p2l->addLayout(notL2);
        auto *notL3 = new QHBoxLayout;
        QLabel *lblPath = new QLabel("Nume fisier");
        notL3->addWidget(lblPath);
        notL3->addWidget(Path);
        notL3->addWidget(btnNotExportHTML);
        notL3->addWidget(btnNotExportCSV);
        p2l->addLayout(notL3);
    }

    template<class T>
    void loadData(T& collection){
        lst->clear();
        for(const auto& l : collection) {
            lst->addItem(QString::fromStdString(l.toString()));
        }
    }

    void update() override{
        loadData(service.getNotificari());
    }

    void init_connect(){
        // lista
        Connect(lst, &QListWidget::itemSelectionChanged, [&](){
            if (lst->selectedItems().isEmpty()) {
                //daca nu e nimic selectat golesc campurile
                Nr->setText("");
                Nume->setText("");
                Suprafata->setText("");
                Tip->setText("");
                return;
            }
            auto *currentItem = lst->selectedItems().at(0);
            Locatar locatar = Locatar::fromString(currentItem->text().toStdString());
            Nr->setText(QString::fromStdString(std::to_string(locatar.getApartament())));
            Nume->setText(QString::fromStdString(locatar.getNumeProprietar()));
            Suprafata->setText(QString::fromStdString(std::to_string(locatar.getSuprafata())));
            Tip->setText(QString::fromStdString(locatar.getTip()));
        });

        //notificari
        Connect(btnNotShow, &QPushButton::clicked, [&](){
            Locatari locatari = service.getNotificari();
            loadData(locatari);
        });
        Connect(btnNotAdd, &QPushButton::clicked, [&](){
            TypeApartament apartament = Nr->text().toInt();
            try {
                service.addNotificare(apartament);
                Locatari loc = service.getNotificari();
                loadData(loc);
            }
            catch(MyException& me) { MsgBox(me.what()); }
        });
        Connect(btnNotClear, &QPushButton::clicked, [&](){
            service.clearNotificari();
            lst->clear();
            MsgBox("Lista de notificari a fost stearsa!");
        });
        Connect(btnNotGen, &QPushButton::clicked, [&](){
            int nr = spinBox->value();
            try{
                service.generateNotificari(nr);
                Locatari loc = service.getNotificari();
                loadData(loc);
            }
            catch(MyException& me) { MsgBox(me.what());}
        });
        Connect(btnNotExportHTML, &QPushButton::clicked, [&](){
            string path = Path->text().toStdString();
            service.exportNotificariHTML(path);
            MsgBox("Export HTML cu succes!");
        });
        Connect(btnNotExportCSV, &QPushButton::clicked, [&](){
            string path = Path->text().toStdString();
            service.exportNotificariCSV(path);
            MsgBox("Export CSV cu succes!");
        });
    }

public:
    explicit GUINotificari(Service& srv) : service{srv} {
        initGUI();
        loadData(service.getNotificari());
        init_connect();
        service.addObserver(this);
    }
    ~GUINotificari() override{
        service.removeObserver(this);
    }
};

#endif //LAB10_GUINOTIF_H
