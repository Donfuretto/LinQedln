#include "loginView.h"
#include <QWidget>
#include <QMap>
#include <iostream>
#include <QMenu>
#include <QMenuBar>
#include <QGridLayout>
#include <QImage>
#include <QPainter>
#include "GUI_Control/controller.h"


//Login crea controller di partenza quindi non lo ha di passaggio.
loginView::loginView(){
    createGridGroupBox();
    // Layout principale della dialog
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(gridGroupBox);

    setLayout(mainLayout);
}

void loginView::createGridGroupBox() {
    gridGroupBox = new QGroupBox;

    QGridLayout* layout = new QGridLayout;

    labels[0] = new QLabel(tr("ID: ").arg(1));
    lineEdits[0] = new QLineEdit;

    labels[1] = new QLabel(tr("PW: ").arg(2));
    lineEdits[1] = new QLineEdit;

    labels[2] = new QLabel("");


    layout->addWidget(labels[0], 0, 0);
    layout->addWidget(lineEdits[0], 0, 1);

    layout->addWidget(labels[1], 1, 0);
    layout->addWidget(lineEdits[1],1,1);

    layout->addWidget(labels[2], 2, 1,0);


    buttons[0] = new QPushButton();
    buttons[0]->setFixedSize (100,35);
    QPixmap pixmap("GUI/Img/loginBs.jpg");
    QIcon ButtonIcon(pixmap);
    buttons[0]->setIcon(ButtonIcon);
    buttons[0]->setIconSize(pixmap.rect().size());

//Connetto bottoni al segnale
    connect(buttons[0], &QPushButton::pressed,this,
                    &loginView::buttonsClickOn);
    connect(buttons[0], &QPushButton::released,this,
                    &loginView::buttonsClickOff);

    connect(buttons[0], &QPushButton::clicked,
                    [=]{speed(lineEdits[0]->text(),lineEdits[1]->text());});


    layout->addWidget(buttons[0],0,2,0,2);
    layout->setColumnStretch (0,10);

    QImage test;
    test.load ("GUI/Img/loginSfondo.jpg");

    gridGroupBox->setLayout(layout);
    QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(test));
    //modifiche widget
    setGeometry(500,250,600,400);
    setFixedSize (350,130);
    setPalette(palette);
    setWindowTitle ("LinQedIn");
    setWindowIcon(QIcon("GUI/Img/loqt.jpg"));
}

class controller;
void loginView::speed(QString x,QString y){

    controller* i=new controller();//Controller rimane in memoria.
    if(i->enter(x,y))
        close();
    else
        errLogin ();
}

void loginView::buttonsClickOn(){
    QPixmap pixmap("GUI/Img/loginBa.jpg");
    QIcon ButtonIcon(pixmap);
    buttons[0]->setIcon(ButtonIcon);
    buttons[0]->setIconSize(pixmap.rect().size());
}
void loginView::buttonsClickOff(){
    QPixmap pixmap("GUI/Img/loginBs.jpg");
    QIcon ButtonIcon(pixmap);
    buttons[0]->setIcon(ButtonIcon);
    buttons[0]->setIconSize(pixmap.rect().size());
}
void loginView::errLogin(){
    labels[2]->setText ("PW o Id errati: Riprovare");
    labels[2]->setStyleSheet("background-color:white;color: red;");
}
