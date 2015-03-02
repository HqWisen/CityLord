#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() :
    ui(new Ui::MainWindow), centralWidget(new QWidget), widgetManager(new WidgetManager), stackedWidget(new QStackedWidget)
{
    ui->setupUi(this);
    setCentralWidget(centralWidget);

    widgetManager->setLoginPage(new Login(this, widgetManager, stackedWidget));
    widgetManager->setMainMenuPage(new MainMenu(this, widgetManager));
    widgetManager->setInPlayPage(new InPlay(this, widgetManager));
    stackedWidget->addWidget(widgetManager->getLoginPage());
    stackedWidget->addWidget(widgetManager->getMainMenuPage());
    stackedWidget->addWidget(widgetManager->getInPlayPage());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(stackedWidget);
    centralWidget->setLayout(layout);
    stackedWidget->setCurrentWidget(widgetManager->getLoginPage());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete widgetManager;
}
