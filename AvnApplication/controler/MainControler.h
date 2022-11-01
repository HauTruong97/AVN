#ifndef MAINCONTROLER_H
#define MAINCONTROLER_H
#include <QtQuick>
#include<QAbstractListModel>
#include <QQmlContext>

class MainControler : public QObject
{
public:
  MainControler();
  explicit MainControler(QObject *parent = nullptr);
};

#endif // MAINCONTROLER_H
