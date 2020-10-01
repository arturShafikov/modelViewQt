#ifndef COMBOBOXITEMDELEGATE_H
#define COMBOBOXITEMDELEGATE_H

#include "QStyledItemDelegate"
#include "QComboBox"
#include "QStringList"
#include "QMetaProperty"
#include "iostream"
#include "entity.h"

class ComboBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    QStringList stringList;
    QList<Country*> *list;
    QStringList generateStringList(const QList<Country*> *list);
    Country *findCountry(QString countryName) const;
public:
    ComboBoxItemDelegate(QObject *parent = nullptr, QList<Country *> *list = nullptr);

    ~ComboBoxItemDelegate();

    QWidget * createEditor(QWidget *parent,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

};

#endif // COMBOBOXITEMDELEGATE_H
