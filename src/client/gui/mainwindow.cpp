#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(char* hostname, int port) :
    ui(new Ui::MainWindow), centralWidget(new QWidget), clientManager(new ClientManagerGUI(hostname, port))
{
    ui->setupUi(this);
    setFixedSize(1152, 864);
    setCentralWidget(centralWidget);

    clientManager->set(ClientManagerGUI::LOGIN, new Login(this, clientManager));
    clientManager->set(ClientManagerGUI::MAINMENU, new MainMenu(this, clientManager));
    clientManager->set(ClientManagerGUI::INGAME, new InGame(this, clientManager));
    clientManager->set(ClientManagerGUI::CREATEACCOUNT, new CreateAccount(this, clientManager));
    clientManager->set(ClientManagerGUI::CREATEGAME, new CreateGame(this, clientManager));
    clientManager->set(ClientManagerGUI::JOINGAME, new JoinGame(this, clientManager));

    centralWidget->setLayout(clientManager->getLayout());
    clientManager->setCurrentWidget(ClientManagerGUI::LOGIN);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete centralWidget;
    delete clientManager;
}
