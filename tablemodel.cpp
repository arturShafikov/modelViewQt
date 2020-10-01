#include "tablemodel.h"

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return companyList->size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    QObject *object = companyList->at(0);
    const QMetaObject *metaObject = object->metaObject();
    return  metaObject->propertyCount()-2;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        QObject *object = companyList->at(0);
        const QMetaObject *metaObject = object->metaObject();
        if (section < metaObject->propertyCount()) {
            QMetaProperty metaProperty = metaObject->property(section+2);
            const char *name = metaProperty.name();
            return QVariant(name);
        }
    }
    return QVariant();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= companyList->size() || index.row() < 0) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QObject *object = companyList->at(index.row());
        const QMetaObject *metaObject = object->metaObject();
        if (index.column() < metaObject->propertyCount()) {
            QMetaProperty metaProperty = metaObject->property(index.column()+2);
            const char *name = metaProperty.name();
            if (metaProperty.type() == QVariant::Type::UserType) {
                return extractObjectName(object->property(name));
            } else {
                return object->property(name);
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        QObject *object = companyList->at(index.row());
        const QMetaObject *metaObject = object->metaObject();
        if (index.column() < metaObject->propertyCount()) {
            QMetaProperty metaProperty = metaObject->property(index.column()+2);
            const char *name = metaProperty.name();
            object->setProperty(name, value);
            emit dataChanged(index, index, {role});
            return true;
        }
    }
    return false;
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; row++) {
        Company *company = new Company();
        companyList->insert(position, company);
    }
    endInsertRows();
    return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row <rows; row++) {
        companyList->removeAt(position);
    }
    endRemoveRows();
    return true;
}

QVariant TableModel::extractObjectName(const QVariant &variant) const
{
    QObject *object = qvariant_cast<QObject *>(variant);
    const QMetaObject *metaObject = object->metaObject();
    int cols = metaObject->propertyCount();
    std::string nameString = "Name";
    for (int i = 1; i < cols; i++) {
        QMetaProperty metaProperty = metaObject->property(i);
        const char *name = metaProperty.name();
        std::string propertyNameString = name;
        if (propertyNameString.find(nameString) != std::string::npos) {
            return object->property(name).toString();
        }
    }
    QMetaProperty metaProperty = metaObject->property(1);
    return object->property(metaProperty.name());
}
