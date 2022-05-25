//
// Created by Daniel on 25.05.2022.
//

#ifndef LAB10_GUINOTIFREADONLY_H
#define LAB10_GUINOTIFREADONLY_H

#include "service.h"
#include "observer.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>
#include "QPainter"
#include <qmessagebox.h>
#include <QtWidgets/qcombobox.h>
#include <QTWidgets/qgridlayout.h>

#define Connect QObject::connect
#define MsgBox(msg) QMessageBox::information(this, "Info", msg);
using Locatari = std::vector<Locatar>;

class GUINotifReadOnly : public QWidget, public Observer{
private:
    Service& service;

    void paintEvent(QPaintEvent* ev) override{
        QPainter p{this};

        int n = service.getNotificari().size();
        int x = 30, y = 30;
        for(int i=0;i<n;++i)
        {
            p.drawImage(x, y, QImage("OwnFiles/imgnotif.png"));
            x+= 100;
            if(x>1000) x = 30, y+=100;
        }
    }

    void update() override{
        repaint();
    }

public:
    explicit GUINotifReadOnly(Service& srv) : service{srv} {
        update();
        service.addObserver(this);
    }
    ~GUINotifReadOnly() override{
        service.removeObserver(this);
    }
};


#endif //LAB10_GUINOTIFREADONLY_H
