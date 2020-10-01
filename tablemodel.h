#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "QAbstractTableModel"
#include "QMetaProperty"
#include "entity.h"
#include "iostream"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QList<Company*> *companyList,
               QObject *parent = nullptr)
        : QAbstractTableModel(parent) {
        this->companyList = companyList;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &index = QModelIndex()) override;
private:
    QList<Company*> *companyList;
    QVariant extractObjectName(const QVariant &variant) const;
};
#endif // TABLEMODEL_H
