#include "LoginWindow.hpp"

LoginWindow::LoginWindow() : QWidget(){
    setWindowTitle("Welcome to CityLord");
    setFixedSize(510,320);
    //construction des boutons
    m_loginButton = new QPushButton("Log in",this);
    m_createButton = new QPushButton("Create account",this);

    m_loginButton->setCursor(Qt::PointingHandCursor);
    m_loginButton->setToolTip("log in the game");
    m_loginButton->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/src/resources/img/53445.png"));
    m_loginButton->move(275,290);

    m_createButton->setCursor(Qt::PointingHandCursor);
    m_createButton->setToolTip("create user & log in");
    m_createButton->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/src/resources/img/53445.png"));
    m_createButton->move(125,290);

    //Connexion du clic du bouton à la fermeture de l'application
    QObject::connect(m_loginButton, SIGNAL(clicked()),this, SLOT(loginFunction()));
    QObject::connect(m_createButton, SIGNAL(clicked()),this, SLOT(createFunction()));

    //construction string username
    m_usernameEntry = new QLineEdit("",this);
    m_usernameEntry->move(205,210);
    m_pwdEntry = new QLineEdit("",this);
    m_pwdEntry->move(205,240);
    QLabel *usernameLabel = new QLabel("Username: ",this);
    QLabel *pwdLabel = new QLabel("Password: ",this);
    usernameLabel->move(125,215);
    pwdLabel->move(125,245);

    QWidget *frame = new QWidget(this);
    frame->setGeometry(5, 5, 500, 200);
    frame->setStyleSheet("background-image: url("+QCoreApplication::applicationDirPath() + "/src/resources/img/CityLordsmall.png"+")");
}

void LoginWindow::loginFunction(){
	std::string username = m_usernameEntry->text().toStdString();	
		
	std::cout<< "Login username = "<<username<<std::endl;
    QMessageBox::warning(this, "Login Dialog", "Sorry we're too dumb 4 dat");
}

void LoginWindow::createFunction(){
    QMessageBox::warning(this, "Create Dialog", "Sorry we're too dumb 4 dat");
}
