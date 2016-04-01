#include "userViewSearch.h"



//Login crea controller di partenza quindi non lo ha di passaggio.
userViewSearch::userViewSearch(QString u){
    createGridGroupBox(u);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(GroupBox);
    setLayout(mainLayout);
}

void userViewSearch::createGridGroupBox(QString u) {
    GroupBox = new QGroupBox;
    QGridLayout* layout = new QGridLayout;

    labels=new QLabel(u);
    layout->addWidget(labels,0,0,2,2);


    QImage test;
    test.load ("GUI/Img/Sfondo.jpg");

    GroupBox->setLayout(layout);
    QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(test));

    //modifiche widget
    setGeometry(500,250,600,400);
    setFixedSize (350,250);
    setPalette(palette);

    setWindowTitle ("LinQedIn");
    setWindowIcon(QIcon("GUI/Img/loqt.jpg"));
}
