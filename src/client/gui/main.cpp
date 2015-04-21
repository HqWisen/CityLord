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
    return a.exec();
}
