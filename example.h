#pragma once
#include<QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <qmessagebox.h>
#include <QtWidgets/qcombobox.h>
#include <QTWidgets/qgridlayout.h>
#include"Service.h"

class LocatarGUI : public QWidget {
    ServiceLocatar& service;
public:
    LocatarGUI(ServiceLocatar& service) :service{ service } {
        initGUI();
        loadData();
        initConnect();
        adaugaButoane(service.getallLocatari());
    }
private:
    QListWidget* lst = new QListWidget;
    QLineEdit* Nr = new QLineEdit;
    QLineEdit* Nume = new QLineEdit;
    QLineEdit* Suprafata = new QLineEdit;
    QLineEdit* Tip = new QLineEdit;
    QLineEdit* txtExtra = new QLineEdit; //camp suplimentar pentru a stabili filtrarea

    QPushButton* btnExit = new QPushButton{ "&Exit" };
    QPushButton* btnAdd = new QPushButton{ "&Add" };
    QPushButton* btnModify = new QPushButton{ "&Modify" };
    QPushButton* btnDelete = new QPushButton{ "&Delete" };
    QPushButton* btnAll = new QPushButton{ "&Show All" };
    QPushButton* btnFTip = new QPushButton{ "&Filter Tip" };
    QPushButton* btnFSup = new QPushButton{ "&Filter suprafata" };
    QPushButton* btnSortSup = new QPushButton{ "Sort suprafata" };
    QPushButton* btnSortNume = new QPushButton{ "Sort name" };
    QPushButton* btnSortTipSup = new QPushButton{ "Sort Tip+suprafata" };
    QPushButton* btnUndo = new QPushButton{ "Undo" };
    QPushButton* btnAddWishList = new QPushButton{ "Add Wishlist" };
    QPushButton* btnAddRandomWishList = new QPushButton{ "Add Random Wishlist" };
    QPushButton* btnDeleteWishList = new QPushButton{ "Delete Wishlist" };

    QComboBox* comboBox = new QComboBox;

    QWidget* btnDyn = new QWidget;
    QVBoxLayout* lyBtnDy = new QVBoxLayout;

    void initConnect() {
        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            close(); });
        QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
            auto numar = Nr->text().toInt();
            auto nume = Nume->text();
            auto sup = Suprafata->text().toDouble();
            auto tip = Tip->text();
            try {
                service.addLocatar(numar, nume.toStdString(), sup, tip.toStdString());
                loadData();
                for (int i = 0; i < lyBtnDy->count(); ++i)
                {
                    QWidget* widget = lyBtnDy->itemAt(i)->widget();
                    if (widget != NULL)
                    {
                        widget->setVisible(false);
                    }
                }
                adaugaButoane(service.getallLocatari());
            }
            catch (ValidateException&) {
                QMessageBox::information(nullptr, "Info", "Datele introduse nu sunt valide!");
            }
            catch (RepoException&) {
                QMessageBox::information(nullptr, "Info", "Locatarul cu nr dat exista deja!");
            }
        });
        QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
            auto numar = Nr->text().toInt();
            auto nume = Nume->text().toStdString();
            auto sup = Suprafata->text().toDouble();
            auto tip = Tip->text().toStdString();
            try {
                service.sterge(numar, nume, sup, tip);
                loadData();
                for (int i = 0; i < lyBtnDy->count(); ++i) {
                    QWidget* widget = lyBtnDy->itemAt(i)->widget();
                    if (widget != 0)
                    {
                        widget->setVisible(false);
                    }
                }
                adaugaButoane(service.getallLocatari());
            }
            catch (RepoException&)
            {
                QMessageBox::information(nullptr, "Info", "Locatarul cu nr dat nu exista!");
            }
        });
        QObject::connect(btnModify, &QPushButton::clicked, [&]() {
            auto numar = Nr->text();
            auto nume = Nume->text();
            auto sup =Suprafata->text();
            auto tip = Tip->text();
            try {
                service.modificaProp(numar.toInt(), nume.toStdString(), sup.toDouble(), tip.toStdString());
                loadData();
            }
            catch (RepoException&) {
                QMessageBox::information(nullptr, "Info", "Locatarul cu nr dat nu exista!");
            }
        });
        QObject::connect(btnFTip, &QPushButton::clicked, [&]() {
            lst->clear();
            auto field = txtExtra->text();
            auto filtered = service.filtrareTip(field.toStdString());
            for (auto& c : filtered) {
                lst->addItem(QString::fromStdString(c.getTipApartament()));
            }
        });

        QObject::connect(btnFSup, &QPushButton::clicked, [&]() {
            lst->clear();
            auto field = txtExtra->text().toDouble();
            auto filtered = service.filtrareSuprafata(field);
            for (auto& c : filtered) {
                lst->addItem(QString::fromStdString(c.getNumeProprietar()));
            }
        });

        QObject::connect(btnSortNume, &QPushButton::clicked, [&]() {
            lst->clear();
            auto sorted = service.sortNume();
            for (auto& c : sorted) {
                lst->addItem(QString::fromStdString(c.getNumeProprietar()));
            }
            for (int i = 0; i < lyBtnDy->count(); ++i)
            {
                QWidget* widget = lyBtnDy->itemAt(i)->widget();
                if (widget != NULL)
                {
                    widget->setVisible(false);
                }
            }
            adaugaButoane(sorted);
        });

        QObject::connect(btnSortSup, &QPushButton::clicked, [&]() {
            lst->clear();
            auto sorted = service.sortSup();
            for (auto& c : sorted) {
                lst->addItem(QString::fromStdString(c.getNumeProprietar()));
                lst->addItem(QString::fromStdString(c.getTipApartament()));
            }
            for (int i = 0; i < lyBtnDy->count(); ++i)
            {
                QWidget* widget = lyBtnDy->itemAt(i)->widget();
                if (widget != NULL)
                {
                    widget->setVisible(false);
                }
            }
            adaugaButoane(sorted);
        });

        QObject::connect(btnSortTipSup, &QPushButton::clicked, [&]() {
            lst->clear();
            auto sorted = service.sortTipSup();
            for (auto& c : sorted) {
                lst->addItem(QString::fromStdString(c.getTipApartament()));
            }
            for (int i = 0; i < lyBtnDy->count(); ++i)
            {
                QWidget* widget = lyBtnDy->itemAt(i)->widget();
                if (widget != NULL)
                {
                    widget->setVisible(false);
                }
            }
            adaugaButoane(sorted);
        });



        QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
        	if (lst->selectedItems().isEmpty()) {
        		//daca nu e nimic selectat golesc campurile
        		Nr->setText(0);
        		Nume->setText("");
        		Suprafata->setText(0);
        		Tip->setText("");
        		return;
        	}
        	QListWidgetItem* currentItem = lst->selectedItems().at(0);
        	Nr->setText(currentItem->text());
        	auto c = service.cauta(currentItem->text().toStdString());
        	Nume->setText(QString::fromStdString(c.getNumeProp()));
        	Suprafata->setText(QString::fromStdString(c.getModel()));
        	Tip->setText(QString::fromStdString(c.getTip()));

        //	});

        //comboBox-ex lab 10
        QObject::connect(comboBox, QOverload<int>::of(&QComboBox::activated), [&](int index) {
            if (comboBox->currentIndex() == 0) {
                loadData();
            }
            else
                try {
                    service.undo();
                    loadData();
                }
                catch (RepoException&) {
                    QMessageBox::information(nullptr, "Info", "Nu se mai poate face undo!");
                }
        });

        /*QObject::connect(btnWishlist, &QPushButton::clicked, [&]() {
            auto wishlist = new WishlistGUI{ service };
            wishlist->show();
            });*/

        //}
    }
    void adaugaButoane(const vector<Locatar>& Loc) {
        for (const auto& c : Loc) {
            auto btn = new QPushButton{ QString::fromStdString(c.getNumeProprietar()) };
            lyBtnDy->addWidget(btn);
            QObject::connect(btn, &QPushButton::clicked, [this, btn, c]() {
                service.sterge(c.getNrAp(), c.getNumeProprietar(), c.getSuprafata(), c.getTipApartament());
                loadData();
                for (int i = 0; i < lyBtnDy->count(); ++i)
                {
                    QWidget* widget = lyBtnDy->itemAt(i)->widget();
                    if (widget != NULL)
                    {
                        widget->setVisible(false);
                    }
                }
                adaugaButoane(service.getallLocatari());
                //lyBtnDy->removeWidget(btn);
            });
        }
    }
    void loadData() {
        lst->clear();
        for (const auto& loc : service.getallLocatari()) {

            lst->addItem(QString::fromStdString(loc.getNumeProprietar()));
            lst->addItem(QString::fromStdString(loc.getTipApartament()));
            //lst->addItem(QString::toStdString(loc.getNrAp()));
        }
    }
    void initGUI() {
        QHBoxLayout* layoutMain = new QHBoxLayout{};
        setLayout(layoutMain);

        layoutMain->addWidget(lst);

        auto layout2 = new QVBoxLayout{};
        auto layout3 = new QVBoxLayout{};
        auto formLayout = new QFormLayout;
        formLayout->addRow("Nr apartament", Nr);
        formLayout->addRow("Nume", Nume);
        formLayout->addRow("Suprafata", Suprafata);
        formLayout->addRow("Tip", Tip);
        formLayout->addRow("Extra field(filter)", txtExtra);
        layout3->addLayout(formLayout);

        auto buttonL = new QHBoxLayout;
        buttonL->addWidget(btnAdd);
        buttonL->addWidget(btnDelete);
        buttonL->addWidget(btnModify);
        //buttonL->addWidget(btnFProd);
        //buttonL->addWidget(btnFTip);
        layout3->addLayout(buttonL);

        auto buttonsLayout = new QHBoxLayout;
        buttonsLayout->addWidget(btnSortNume);
        buttonsLayout->addWidget(btnSortSup);
        buttonsLayout->addWidget(btnSortTipSup);

        //Grid Layout-ex lab 10
        QGridLayout* gridLayout = new QGridLayout;
        gridLayout->addWidget(btnFSup);
        gridLayout->addWidget(btnFTip);
        gridLayout->addWidget(comboBox);
        gridLayout->addWidget(btnAddWishList);
        gridLayout->addWidget(btnExit);

        layout2->addLayout(layout3);
        layout2->addLayout(buttonsLayout);
        layoutMain->addLayout(layout2);

        comboBox->addItem("All");
        comboBox->addItem("Undo");
        layoutMain->addLayout(gridLayout);


        btnDyn->setLayout(lyBtnDy);
        layoutMain->addWidget(btnDyn);
    }

};
