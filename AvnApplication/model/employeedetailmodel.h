#ifndef EMPLOYEEDETAILMODEL_H
#define EMPLOYEEDETAILMODEL_H
#include<QVector>
#include<QString>
#include <QtQuick>
#include<QAbstractListModel>

struct MyListItem
{
    QString icon;
    QString language;
    int point;
};

class EmployeeDetailModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString getEmployeesName READ getEmployeesName WRITE setEmployeesName NOTIFY employeesNameChanged)
    Q_ENUMS(MyRoles)
public:
    explicit EmployeeDetailModel(QObject *parent = 0);

    enum MyRoles {icon=Qt::UserRole+1, language, point};

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QHash<int, QByteArray> roleNames() const;

    QList<MyListItem> m_list = {
        { "/data/assembly.png", "Assembly", 20 },
        { "/data/cplus.png", "C++", 42 },
        { "/data/javascript.png", "Java", 80 },
        { "/data/qml.png", "Qml", 30 },
        { "/data/opengl.png", "Opengl", 30 }
    };

    Q_INVOKABLE void requestToControllerChangeName(QString name);
    void setEmployeesName(QString value);
    QString getEmployeesName();
    QString m_employeesName = "Moby-Dick";

signals:
    void employeesNameChanged();

};

#endif // EMPLOYEEDETAILMODEL_H
