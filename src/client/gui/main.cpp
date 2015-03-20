#include "mainwindow.h"
#include <QApplication>

#define PORT 27000

int main(int argc, char *argv[])
{
    QApplication::setStyle("plastique");
    QApplication a(argc, argv);

    char* hostname;
    if(argc != 2){
      printf("Hostname not given !\n");
      hostname = "localhost";
    }
    else{
          hostname = argv[1];
    }
    MainWindow mainWindow(hostname, PORT);
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
