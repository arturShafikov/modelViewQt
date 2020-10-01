#include "comboboxitemdelegate.h"

QStringList ComboBoxItemDelegate::generateStringList(const QList<Country *> *list)
{
    QObject *object = list->at(0);
    const QMetaObject *metaObject = object->metaObject();
    int cols = metaObject->propertyCount();
    std::string nameString = "Name";
    int nameCol = 1;
    const char *nameProperty;
    for (int i = 1; i < cols; i++) {
        QMetaProperty metaProperty = metaObject->property(i);
        const char *name = metaProperty.name();
        nameProperty = name;
        std::string propertyNameString = name;
        if (propertyNameString.find(nameString) != std::string::npos) {
            nameCol = i;
            break;
        }
    }
    QStringList stringList;
    for (int i = 0; i < list->size(); i++) {
        QObject *object = list->at(i);
        stringList.push_back(object->property(nameProperty).toString());
    }
    return stringList;
}

Country* ComboBoxItemDelegate::findCountry(QString countryName) const
{
    for (int i = 0; i < list->size(); i++) {
        if (list->at(i)->getCountryName() == countryName) {
            return list->at(i);
        }
    }
    return nullptr;
}

ComboBoxItemDelegate::ComboBoxItemDelegate(QObject *parent, QList<Country *> *list)
    : QStyledItemDelegate(parent) {
    this->list = list;
    stringList = generateStringList(list);
}


ComboBoxItemDelegate::~ComboBoxItemDelegate()
{

}

QWidget *ComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *cb = new QComboBox(parent);
    for (int i = 0; i < stringList.size(); i++) {
     cb->addItem(stringList.at(i));
    }
    return cb;
}

void ComboBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    const QString currentText = index.data(Qt::EditRole).toString();
    const int cbIndex = cb->findText(currentText);
    if (cbIndex >= 0) {
        cb->setCurrentIndex(cbIndex);
    }
}

void ComboBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    Country *country = findCountry(cb->currentText());
    QVariant variant;
    variant.setValue(country);
    model->setData(index, variant, Qt::EditRole);
}
