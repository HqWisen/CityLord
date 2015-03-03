#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() :
    ui(new Ui::MainWindow), centralWidget(new QWidget), clientManager(new ClientManager)
{
    ui->setupUi(this);
    setCentralWidget(centralWidget);

<<<<<<< HEAD
    clientManager->set(ClientManager::LOGIN, new Login(this, clientManager));
    clientManager->set(ClientManager::MAINMENU, new MainMenu(this, clientManager));
    //ClientManager->set(ClientManager::INPLAY, new InPlay(this, clientManager));
    clientManager->set(ClientManager::CREATEACCOUNT, new CreateAccount(this, clientManager));
    clientManager->set(ClientManager::CREATEGAME, new CreateGame(this, clientManager));
=======
    widgetManager->set(WidgetManager::LOGIN, new Login(this, widgetManager));
    widgetManager->set(WidgetManager::MAINMENU, new MainMenu(this, widgetManager));
    //widgetManager->set(WidgetManager::INPLAY, new InPlay(this, widgetManager));
    widgetManager->set(WidgetManager::CREATEACCOUNT, new CreateAccount(this, widgetManager));
    widgetManager->set(WidgetManager::CREATEGAME, new CreateGame(this, widgetManager));
    widgetManager->set(WidgetManager::JOINGAME, new CreateGame(this, widgetManager));
>>>>>>> 8947808f1fbea653d2706b8cb98785f6eaf305c8

    centralWidget->setLayout(clientManager->getLayout());
    clientManager->setCurrentWidget(ClientManager::LOGIN);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete centralWidget;
    delete clientManager;
}
