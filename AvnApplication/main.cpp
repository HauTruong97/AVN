#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <model/SortFilterProxyModel.h>
#include <model/EmployeeDetailModel.h>
#include <model/employeesmodel.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<SortFilterProxyModel>("sortHT", 1, 0, "SortFilterProxyModel");
    EmployeeDetailModel employee;
    EmployeesModel employeesModel;
    engine.rootContext()->setContextProperty("employee", &employee);
    engine.rootContext()->setContextProperty("employeesModel", &employeesModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
