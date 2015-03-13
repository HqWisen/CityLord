#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(char* hostname, int port) :
    ui(new Ui::MainWindow), centralWidget(new QWidget), clientManager(new ClientManager(hostname, port))
{
    ui->setupUi(this);
    setFixedSize(1152, 864);
    setCentralWidget(centralWidget);

    clientManager->set(ClientManager::LOGIN, new Login(this, clientManager));
    clientManager->set(ClientManager::MAINMENU, new MainMenu(this, clientManager));
    clientManager->set(ClientManager::INGAME, new InGame(this, clientManager));
    clientManager->set(ClientManager::CREATEACCOUNT, new CreateAccount(this, clientManager));
    clientManager->set(ClientManager::CREATEGAME, new CreateGame(this, clientManager));
    clientManager->set(ClientManager::JOINGAME, new JoinGame(this, clientManager));

    centralWidget->setLayout(clientManager->getLayout());
    clientManager->setCurrentWidget(ClientManager::LOGIN);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete centralWidget;
    delete clientManager;
}
