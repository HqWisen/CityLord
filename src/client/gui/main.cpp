#include <QApplication>
#include "LoginWindow.hpp"
//#include <QtGui> //inclut toute les classes du module GUI

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWindow login;
    //affichage de la fenêtre
    login.show();

    return app.exec();
}
