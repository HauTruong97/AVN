#include "EmployeeDetailModel.h"
#include "EmployeesModel.h"

EmployeeDetailModel::EmployeeDetailModel(QObject *parent) : QAbstractListModel(parent)
{

}

int EmployeeDetailModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_list.size();
}

QVariant EmployeeDetailModel::data(const QModelIndex &index, int role) const
{
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const MyListItem &item = m_list.at(index.row());
    if (role == icon) return item.icon;
    if (role == language) return item.language;
    if (role == point) return item.point;

    return {};
}

QHash<int, QByteArray> EmployeeDetailModel::roleNames() const
{
    return { { icon, "icon" },
        { language, "language" },
        { point, "point" },
    };
}

void EmployeeDetailModel::requestToControllerUpdateInfor(QString name, int index)
{
    setEmployeesName(name);
    QList<MyListItem> m_lisbk = {
        { "/data/assembly.png", "Assembly", index + 10 },
        { "/data/cplus.png", "C++", index },
        { "/data/javascript.png", "Java", index + 20 },
        { "/data/qml.png", "Qml", 30 },
        { "/data/opengl.png", "Opengl", index }
    };
    m_list.clear();
    m_list.append(m_lisbk);
    emit endResetModel();
}

void EmployeeDetailModel::setEmployeesName(QString value)
{
    if(value != m_employeesName){
        m_employeesName = value;
        emit employeesNameChanged();
    }
}

QString EmployeeDetailModel::getEmployeesName()
{
    return m_employeesName;
}
