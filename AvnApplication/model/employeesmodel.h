#ifndef EMPLOYEESMODEL_H
#define EMPLOYEESMODEL_H
#include<QVector>
#include<QString>
#include <QtQuick>
#include<QAbstractListModel>

struct MyListItemEmployeesModel
{
    QString name;
    QString avrage;
};

class EmployeesModel: public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(MyRoles)
public:
    explicit EmployeesModel(QObject *parent = 0);

    enum MyRoles {name=Qt::UserRole+1, avrage};

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QHash<int, QByteArray> roleNames() const;

    QList<MyListItemEmployeesModel> m_list = {
        { "Moby-Dick", "2"},
        { "Cat’s Cradle", "3"},
        { "It", "4"},
        { "On the Road", "5"},
        { "Of Mice and Men", "8"},
        { "Do Androids Dream", "9"},
        { "Uncle Tom’s Cabin", "12"},
        { "Uncle Tom’s Cabin", "12"},
        { "Uncle Tom’s Cabin", "12"},
        { "Uncle Tom’s Cabin", "12"}
    };
};

#endif // EMPLOYEESMODEL_H
