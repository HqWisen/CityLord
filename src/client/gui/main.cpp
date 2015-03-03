#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    //mainWindow.setWindowState(Qt::WindowFullScreen);
    //mainWindow.showFullScreen();


    /*InPlay w;
    w.show();

    Login l;
    l.show();

    MainMenu m;
    m.show();
    */
    //test
    /*QWidget window;
    window.setFixedSize(1200,800);

    Login l(&window);
    l.show();
    l.move(345,235);
    //MainMenu testMenu(&window);

    window.show();    */

    return a.exec();
}
