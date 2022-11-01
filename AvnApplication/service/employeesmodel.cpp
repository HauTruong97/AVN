#include "EmployeesModel.h"

EmployeesModel::EmployeesModel(QObject *parent) : QAbstractListModel(parent)
{

}

int EmployeesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_list.size();
}

QVariant EmployeesModel::data(const QModelIndex &index, int role) const
{
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const MyListItemEmployeesModel &item = m_list.at(index.row());
    if (role == name) return item.name;
    if (role == average) return item.average;

    return {};
}

QHash<int, QByteArray> EmployeesModel::roleNames() const
{
    return { { name, "name" },
        { average, "average" }
    };
}
