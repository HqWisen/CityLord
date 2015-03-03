#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() :
    ui(new Ui::MainWindow), centralWidget(new QWidget), clientManager(new ClientManager)
{
    ui->setupUi(this);
    setCentralWidget(centralWidget);

    clientManager->set(ClientManager::LOGIN, new Login(this, clientManager));
    clientManager->set(ClientManager::MAINMENU, new MainMenu(this, clientManager));
    //ClientManager->set(ClientManager::INPLAY, new InPlay(this, clientManager));
    clientManager->set(ClientManager::CREATEACCOUNT, new CreateAccount(this, clientManager));
    clientManager->set(ClientManager::CREATEGAME, new CreateGame(this, clientManager));

    centralWidget->setLayout(clientManager->getLayout());
    clientManager->setCurrentWidget(ClientManager::LOGIN);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete centralWidget;
    delete clientManager;
}
