#include "editUserProfile.h"
#include <QWidget>
#include <QMap>
#include <iostream>
#include <QMenu>
#include <QMenuBar>
#include <QGridLayout>
#include <QComboBox>
#include <QLayout>
#include <QImage>
#include <QPainter>
#include <QPicture>
#include <QDir>
#include <QScrollArea>
#include <QDesktopServices>
#include <QFileDialog>

EditUserProfile::EditUserProfile(Profile* i, controller* x):id(i->idInfo.get_name()),i(x),profile(i){
    createHomeEdit();
    drawInfo ();
    QImage ImgF;
    ImgF.load ("GUI/Img/Sfondo.jpg");
    QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(ImgF));
    setPalette(palette);

    mainLayout = new QGridLayout();

    mainLayout->addWidget(superTopGroupBox,0,0,1,12,Qt::AlignTop);//Navigazione home
    mainLayout->addWidget(topGroupBox,1,1,1,11,Qt::AlignTop);//navigazione editProfile
    mainLayout->addWidget(rightGroupBox,2,1,2,11);//view dati
    mainLayout->addWidget(SaveBGroupBox,1,0,3,1,Qt::AlignLeft);//Bulsante save
    mainLayout->setColumnStretch(1,0);
    setLayout(mainLayout);

    //Impostazioni finestra
    setWindowTitle("LinQedIn-User: "+i->idInfo.get_mail());
    setWindowIcon (QIcon("GUI/Img/loqt.jpg"));
    setLayoutDirection(Qt::LeftToRight);

}

void EditUserProfile::createHomeEdit() {

    topGroupBox = new QGroupBox;
    superTopGroupBox=new QGroupBox;
    rightGroupBox= new QGroupBox;
    imageProfile=new QGroupBox;
    SaveBGroupBox=new QGroupBox;

    //SuperTop
    QGridLayout* layout = new QGridLayout;
    buttons[0] = new QPushButton("Home");
        buttons[0]->setFixedSize (75,50);
        buttons[0]->setIcon(QIcon("GUI/Icon/icon_house"));
    buttons[1] = new QPushButton("Immagine");
        buttons[1]->setFixedSize (125,50);
        buttons[1]->setIcon(QIcon("GUI/Icon/icon_image"));
    buttons[7] = new QPushButton("Password");
        buttons[7]->setFixedSize (125,50);
        buttons[7]->setIcon(QIcon("GUI/Icon/icon_key"));

    layout->addWidget(buttons[1],0,0);
    layout->addWidget(buttons[7],0,1);
    layout->addWidget(buttons[0],0,2,Qt::AlignRight);

    connect(buttons[0], &QPushButton::clicked,this,&EditUserProfile::home);
    connect(buttons[7], &QPushButton::clicked,this,&EditUserProfile::callChangePw);
    connect(buttons[1], &QPushButton::clicked,this,&EditUserProfile::callChangeImage);
    //Top
    QGridLayout* layout2 = new QGridLayout;

    buttons[3] = new QPushButton("Personali");
    buttons[3]->setFixedSize (75,25);
    buttons[4] = new QPushButton("Lavoro");
    buttons[4]->setFixedSize (75,25);
    buttons[5] = new QPushButton("Formazione");
    buttons[5]->setFixedSize (75,25);
    buttons[6] = new QPushButton("Esperienze");
    buttons[6]->setFixedSize (75,25);

    layout2->addWidget(buttons[3],0,0);
    layout2->addWidget(buttons[4],0,1);
    layout2->addWidget(buttons[5],0,2);
    layout2->addWidget(buttons[6],0,3);

    connect(buttons[3], &QPushButton::clicked,this,&EditUserProfile::drawInfo);
    connect(buttons[4], &QPushButton::clicked,this,&EditUserProfile::drawWork);
    connect(buttons[5], &QPushButton::clicked,this,&EditUserProfile::drawForm);
    connect(buttons[6], &QPushButton::clicked,this,&EditUserProfile::drawEsp);

    //Gestione Img Profilo
    QGridLayout* layoutTop=new QGridLayout;

    imageProfile->setLayout (layoutTop);
    imageProfile->setFixedSize (150,175);
    imageProfile->setAlignment (Qt::AlignCenter);

    superTopGroupBox->setLayout (layout);
    topGroupBox->setLayout(layout2);


    QImage imgP;
    imgP.load((QString)(profile->ViewImage()));
    QGridLayout* layoutSave=new QGridLayout;
    imgProfile=new QLabel;
    imgProfile->setPixmap (QPixmap::fromImage (imgP));

    layoutSave->addWidget(imgProfile,0,0,Qt::AlignCenter);
    buttons[9] = new QPushButton("Salva Modifiche");
    buttons[9]->setIcon(QIcon("GUI/Icon/icon_floppy_alt"));
    layoutSave->addWidget (buttons[9]);
    SaveBGroupBox->setLayout (layoutSave);
    buttons[9]->disconnect();
//modifiche widget

    setGeometry(500,250,600,400);
}
void EditUserProfile::setId (QString i){
    id=i;
}
void EditUserProfile::setC (controller * x){//setto controller
    i=x;
}

void EditUserProfile::home(){
    i->editProfileCallHome();
}

void EditUserProfile::callEditProfile(){
    i->userEditProfile();
}

void EditUserProfile::drawInfo (){
    lineLabel[0]=new QLabel("Nome: ");
    lineLabel[1]=new QLabel("Cognome: ");
    lineLabel[2]=new QLabel("Indirizzo: ");
    lineLabel[3]=new QLabel("Mail: ");
    lineLabel[4]=new QLabel(profile->idInfo.get_mail());
    lineEdits[0]=new QLineEdit(profile->idInfo.get_name ());
    lineEdits[1]=new QLineEdit(profile->idInfo.get_lastname ());
    lineEdits[2]=new QLineEdit(profile->idInfo.get_provenienza ());

    if(rightGroupBox->layout ()){//Se esiste già un layout
        QGridLayout* layout = dynamic_cast<QGridLayout*>(rightGroupBox->layout ());

        //Pulisco layout.
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0){
                child->widget()->deleteLater();
            delete child;
        }
        for(int i=0;i<3;++i){
            layout->addWidget (lineLabel[i],i,0);
            layout->addWidget (lineEdits[i],i,1);
        }
        layout->addWidget(lineLabel[3],3,0);
        layout->addWidget(lineLabel[4],3,1);
    }
    else{
        QGridLayout* layout = new QGridLayout;
        for(int i=0;i<3;++i){
            layout->addWidget (lineLabel[i],i,0);
            layout->addWidget (lineEdits[i],i,1);
        }
        layout->addWidget(lineLabel[3],3,0);
        layout->addWidget(lineLabel[4],3,1);
        rightGroupBox->setLayout (layout);
    }
    buttons[9]->disconnect();
    connect(buttons[9], &QPushButton::clicked,this,&EditUserProfile::callSaveInfo);
}

void EditUserProfile::drawForm(){
    lineLabel[0]=new QLabel("Titolo: ");
    lineLabel[1]=new QLabel("Settore: ");
    lineLabel[4]=new QLabel("Descrizione: ");
    lineLabel[3]=new QLabel("Pubblicazioni: ");
    lineLabel[2]=new QLabel("Valutazione: ");
    lineLabel[5]=new QLabel("Premi: ");

    Formazione x=profile->idInfo.get_formazione ();
    lineEdits[0]=new QLineEdit(x.get_title ());
    lineEdits[1]=new QLineEdit(x.get_sector ());
    lineEdits[4]=new QLineEdit(x.get_descriction ());
    lineEdits[3]=new QLineEdit(x.get_activity());
    lineEdits[2]=new QLineEdit(x.get_valutation ());
    lineEdits[5]=new QLineEdit(x.get_award ());

    QGridLayout* layout = dynamic_cast<QGridLayout*>(rightGroupBox->layout ());

    //Pulisco layout.
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
        child->widget()->deleteLater();
        delete child;
    }

    for(int i=0;i<6;++i){
        layout->addWidget (lineLabel[i],i,0);
        layout->addWidget (lineEdits[i],i,1);
    }
    buttons[9]->disconnect();
    connect(buttons[9], &QPushButton::clicked,this,&EditUserProfile::callSaveForm);
}

void EditUserProfile::drawEsp(){

    Info x=profile->idInfo;
    QVector<Esperienza> esp=profile->idInfo.get_esperienze();

    QGridLayout* layout = dynamic_cast<QGridLayout*>(rightGroupBox->layout());
    QGridLayout* layout2= new QGridLayout();

    QPushButton* Buttonadd=new QPushButton("Aggiungi una tua esperienza");
    Buttonadd->setIcon (QIcon("GUI/Icon/icon_plus_alt"));
        connect(Buttonadd, &QPushButton::clicked,this,&EditUserProfile::showAddEsp);
    QPushButton* Buttondel[esp.size()];

    //Pulisco layout.
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
        child->widget()->deleteLater();
        delete child;
    }
    layout2->addWidget (Buttonadd,0,0);
    for(int i=0;i<esp.size();++i){

        lineLabel[0]=new QLabel("Azienda: "+esp[i].get_titolo ());
        lineLabel[1]=new QLabel("Ruolo: "+esp[i].get_nomeazienda ());
        lineLabel[2]=new QLabel("Località: "+esp[i].get_localita ());
        lineLabel[3]=new QLabel("Periodo: "+esp[i].get_periodo ());

        Buttondel[i]=new QPushButton("DEL");
        Buttondel[i]->setIcon (QIcon("GUI/Icon/icon_trash"));
        connect(Buttondel[i], &QPushButton::clicked,[=]{callDelEsp(i);});

        layout2->addWidget (lineLabel[0]);
        layout2->addWidget (lineLabel[1]);
        layout2->addWidget (lineLabel[2]);
        layout2->addWidget (lineLabel[3]);
        layout2->addWidget (Buttondel[i]);
    }

    buttons[9]->disconnect();
    connect(buttons[9], &QPushButton::clicked,this,&EditUserProfile::callSaveEsp);

    QScrollArea *area = new QScrollArea(this);
    QWidget* y=new QWidget();
    area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    area->setWidget(y);
    area->setWidgetResizable (true);
    y->setLayout(layout2);

    layout->addWidget(area);
}

void EditUserProfile::drawWork(){
        lineLabel[0]=new QLabel("Lavoro: ");
        lineLabel[1]=new QLabel("Interessi: ");
        lineLabel[2]=new QLabel("Lingue: ");
        lineLabel[3]=new QLabel("Settore: ");

        Info x=profile->idInfo;
        lineEdits[0]=new QLineEdit(x.get_lavoro ());
        lineEdits[1]=new QLineEdit(x.get_interessi ());
        lineEdits[2]=new QLineEdit(x.get_lingue ());
        lineEdits[3]=new QLineEdit(x.get_settore ());

        QGridLayout* layout = dynamic_cast<QGridLayout*>(rightGroupBox->layout ());
        QLayoutItem *child;//Pulisco layout.
        while ((child = layout->takeAt(0)) != 0) {
            child->widget()->deleteLater();
            delete child;
        }

        for(int i=0;i<4;++i){
            layout->addWidget (lineLabel[i],i,0);
            layout->addWidget (lineEdits[i],i,1);
        }
        buttons[9]->disconnect();
        connect(buttons[9], &QPushButton::clicked,this,&EditUserProfile::callSaveWork);
}

void EditUserProfile::callSaveInfo(){
    QVector<QString> x;
    for(int i=0;i<3;i++)
        x.push_back(lineEdits[i]->text ());
    i->userSaveInfo(x);
}

void EditUserProfile::callSaveWork(){
    QVector<QString> x;
    for(int i=0;i<4;i++)
        x.push_back(lineEdits[i]->text ());
    i->userSaveWork(x);
}

void EditUserProfile::callSaveForm(){
    QVector<QString> x;
    for(int i=0;i<6;i++)
        x.push_back (lineEdits[i]->text ());
    i->userSaveForm(x);
}

void EditUserProfile::callSaveEsp(){}

void EditUserProfile::callDelEsp (int x){
    i->userDelEsp (x);
}


void EditUserProfile::showAddEsp (){
    QGridLayout* layoutNewEsp=new QGridLayout;
    int num=4;
    QLabel* line[num];
    QPushButton* Button=new QPushButton("Inserisci esperienza");
    Button->setIcon (QIcon("GUI/Icon/icon_plus_alt"));
    line[0]=new QLabel("Ruolo: ");
    line[1]=new QLabel("Azienda: ");
    line[2]=new QLabel("Località: ");
    line[3]=new QLabel("Periodo: ");

    lineEdits[5]=new QLineEdit();
    lineEdits[6]=new QLineEdit();
    lineEdits[7]=new QLineEdit();
    lineEdits[8]=new QLineEdit();

    layoutNewEsp->addWidget (line[0],0,0);
    layoutNewEsp->addWidget (line[1],1,0);
    layoutNewEsp->addWidget (line[2],2,0);
    layoutNewEsp->addWidget (line[3],3,0);


    layoutNewEsp->addWidget (lineEdits[5],0,1);
    layoutNewEsp->addWidget (lineEdits[6],1,1);
    layoutNewEsp->addWidget (lineEdits[7],2,1);
    layoutNewEsp->addWidget (lineEdits[8],3,1);

    layoutNewEsp->addWidget (Button,4,1);

    connect(Button, &QPushButton::clicked,this,&EditUserProfile::callAddEsp);

    QWidget* x=new QWidget();
    connect(Button, &QPushButton::clicked,[=]{x->close();});
    x->setLayout (layoutNewEsp);

    QImage ImgF;
        ImgF.load ("GUI/Img/Sfondo.jpg");
    QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(ImgF));
    x->setPalette(palette);
    x->setWindowTitle("LinQedIn-User: "+id);
    x->setWindowIcon (QIcon("GUI/Img/loqt.jpg"));
    x->show ();
}

void EditUserProfile::callAddEsp (){

    QVector<QString> x;
    x.push_back (lineEdits[5]->text ());
    x.push_back (lineEdits[6]->text ());
    x.push_back (lineEdits[7]->text ());
    x.push_back (lineEdits[8]->text ());
    i->userNewEsp (x);
}

void EditUserProfile::callChangeImage (){
    QString file = QFileDialog::getOpenFileName(
                            this,
                            "Seleziona Immagine",
                            "dataBase/ImgProfile",
                            "Images (*.png *.xpm *.jpg)");
    if(!file.isEmpty ())
    i->userCallUpImage (file);
}

void EditUserProfile::updateProfile(Profile* x){
    ExcError("PROFILO AGGIORNATO",0);
    profile=x;
}

void EditUserProfile::callChangePw(){
    i->userCallChangePw();
}
