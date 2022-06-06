//
// Created by Daniel on 25.05.2022.
//

#ifndef LAB10_QTINCLUDES_H
#define LAB10_QTINCLUDES_H


#include <QtWidgets/qwidget.h>
#include <QtWidgets/qtablewidget.h>
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
#include "QPainter"
#include "QDebug"

#define Connect QObject::connect
#define MsgBox(msg) QMessageBox::information(NULL, "Info", msg);
using Locatari = std::vector<Locatar>;

#endif //LAB10_QTINCLUDES_H
