//
// Created by Daniel on 25.05.2022.
//

#ifndef LAB10_MODELS_H
#define LAB10_MODELS_H

#include "QTIncludes.h"
#include "service.h"

class LocatarTableModel : public QAbstractTableModel {
private:
    vector<Locatar> displayed;
public:
    LocatarTableModel() {}
    int rowCount(const QModelIndex& index = QModelIndex()) const override{
        return displayed.size();
    }
    int columnCount(const QModelIndex& index = QModelIndex()) const override{
        return 4; // domain.size()
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        int row = index.row();
        int column = index.column();
        const Locatar& curent = displayed[row];
        if(role == Qt::DisplayRole){
            if(column == 0) return QString::fromStdString(std::to_string(curent.getApartament()));
            if(column == 1) return QString::fromStdString(curent.getNumeProprietar());
            if(column == 2) return QString::fromStdString(std::to_string(curent.getSuprafata()));
            if(column == 3) return QString::fromStdString(curent.getTip());
        }
        if(role==Qt::UserRole){
            return QString::fromStdString(std::to_string(curent.getApartament()));
        }
        return QVariant{};
    }
    Qt::ItemFlags flags(const QModelIndex & /*index*/) const {
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }
    void setElems(const vector<Locatar>& elems){
        //QMessageBox::information(nullptr, "", "Set Elems called");
        displayed = elems;
        //QMessageBox::information(nullptr, "", std::to_string(displayed.size()).c_str());
        QModelIndex topleft = createIndex(0, 0);
        QModelIndex bottomright = createIndex(elems.size()+1, columnCount());
        emit dataChanged(topleft, bottomright);
        emit layoutChanged();
        //QMessageBox::information(nullptr, "", "semnal emis");
    }
};

#endif //LAB10_MODELS_H
