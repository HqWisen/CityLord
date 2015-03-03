#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() :
    ui(new Ui::MainWindow), centralWidget(new QWidget), widgetManager(new WidgetManager)
{
    ui->setupUi(this);
    setCentralWidget(centralWidget);

    widgetManager->set(WidgetManager::LOGIN, new Login(this, widgetManager));
    widgetManager->set(WidgetManager::MAINMENU, new MainMenu(this, widgetManager));
    //widgetManager->set(WidgetManager::INPLAY, new InPlay(this, widgetManager));
    widgetManager->set(WidgetManager::CREATEACCOUNT, new CreateAccount(this, widgetManager));
    widgetManager->set(WidgetManager::CREATEGAME, new CreateGame(this, widgetManager));

    centralWidget->setLayout(widgetManager->getLayout());
    widgetManager->setCurrentWidget(WidgetManager::LOGIN);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete centralWidget;
    delete widgetManager;
}
