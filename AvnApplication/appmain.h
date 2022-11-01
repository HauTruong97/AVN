#ifndef APPMAIN_H
#define APPMAIN_H
#include <QQmlContext>
#include<controler/MainControler.h>

class appMain
{
public:
    appMain(QQmlContext *context);
    MainControler *mainController;
};

#endif // APPMAIN_H
