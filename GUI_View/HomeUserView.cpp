#include "HomeUserView.h"
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
#include "GUI_Control/controller.h"

homeUserView::homeUserView(QString i,QString iM):id(i),linkImage(iM){

    createHomeUser();

    //Imposta layout che mostra info in home
    layoutHome=new QGridLayout;
    ViewGroupBox->setLayout (layoutHome);


    // Layout principale della dialog
    QGridLayout* mainLayout = new QGridLayout();

    QImage imageBackground;
    imageBackground.load ("GUI/Img/Sfondo.jpg");
    imageBackground.scaled (800,500);

    QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(imageBackground));
    setPalette(palette);

    //gestioneGroupBox
    mainLayout->addWidget(imageProfile,0,0,1,1,Qt::AlignLeft);//image
    mainLayout->addWidget(leftGroupBox,1,0,3,1,Qt::AlignLeft);//bulsanti
    mainLayout->addWidget(ViewGroupBox,1,1,3,2);//View
    mainLayout->addWidget(rightGroupBox,0,1,1,2,Qt::AlignTop);//Ricerca
    mainLayout->setColumnStretch(1,0);
    mainLayout->setSpacing (0);
    setLayout(mainLayout);
    //Impostazioni finestra
    setWindowTitle("LinQedIn-User: "+i);
    setWindowIcon (QIcon("GUI/Img/loqt.jpg"));
    setFixedSize (800,600);
    setLayoutDirection(Qt::LeftToRight);
}
void homeUserView::createHomeUser() {

    leftGroupBox = new QGroupBox;
    rightGroupBox= new QGroupBox;
    imageProfile=new QGroupBox;
    ViewGroupBox=new QGroupBox;

    QGridLayout* layout2 = new QGridLayout;
    QComboBox* combos=new QComboBox;

    lineEdits[0] = new QLineEdit("");
    layout2->addWidget(lineEdits[0], 0, 1);

    combos->addItem("Nome");
    combos->addItem("Cogmone");
    combos->addItem("Provenienza");
    combos->addItem("Settore");
    combos->addItem("Lavoro");
    combos->addItem("Lingue");

    layout2->addWidget(combos, 0, 3);
    buttons[3] = new QPushButton();
    buttons[3]->setFixedSize (75,50);
    buttons[3]->setIcon (QIcon("GUI/Icon/icon_search2"));
    layout2->addWidget (buttons[3],0,0);
    layout2->setColumnStretch (0,0);

    QVBoxLayout* layout = new QVBoxLayout;

    //Gestione Img Profilo
    QGridLayout* layoutTop=new QGridLayout;
    QImage imgP;
    imgP.load(linkImage);//loqt.jpg");
    imgProfile=new QLabel;
    imgProfile->setPixmap (QPixmap::fromImage (imgP).scaled (150,150));
    layoutTop->addWidget (imgProfile);

    buttons[0] = new QPushButton("Home");
        buttons[0]->setFixedSize (150,75);
        buttons[0]->setIcon (QIcon("GUI/Icon/icon_house"));

    buttons[1] = new QPushButton("Profilo");
        buttons[1]->setFixedSize (150,75);
        buttons[1]->setIcon (QIcon("GUI/Icon/icon_id_alt"));

    buttons[2] = new QPushButton("Rete");
        buttons[2]->setFixedSize (150,75);
        buttons[2]->setIcon (QIcon("GUI/Icon/icon_contacts"));

    layout->addWidget(buttons[0]);
    layout->addWidget(buttons[1]);
    layout->addWidget(buttons[2]);
    layout->addWidget(buttons[3]);
    layout->addStretch ();

    connect(buttons[0], &QPushButton::clicked,this,&homeUserView::home);
    connect(buttons[1], &QPushButton::clicked,this,&homeUserView::callViewProfile);
    connect(buttons[2], &QPushButton::clicked,this,&homeUserView::callNet);
    connect(buttons[3], &QPushButton::clicked,[=]{
        QVector<int> x;
        x.push_back(combos->currentIndex ());
        QVector<QString> y;
        y.push_back(lineEdits[0]->text ());
        callSearch(x,y);});

    imageProfile->setLayout (layoutTop);

    imageProfile->setFixedSize (200,200);
    imageProfile->setAlignment (Qt::AlignCenter);
    leftGroupBox->setLayout(layout);
    rightGroupBox->setLayout(layout2);


    setGeometry(500,250,600,400);
}

void homeUserView::setId (QString i){
    id=i;
}

void homeUserView::setC (controller *x){//setto controller
    i=x;
}

void homeUserView::printResearch(QVector<User*>* t){
    QGridLayout* layout = dynamic_cast<QGridLayout*>(ViewGroupBox->layout ());
    QGridLayout* layout2 = new QGridLayout();
    if(t){
        QLabel* lineLabel[t->size ()];
        QImage* lineImage[t->size ()];
        QLabel* lineLabelImage[t->size ()];
        QPushButton* lineView[t->size()];
        QPushButton* lineButton[t->size()];

        for(int i=0;i<t->size();i++)
        {
            lineImage[i]=new QImage((*t)[i]->get_pf().ViewImage());
            lineLabelImage[i]=new QLabel;
                lineLabelImage[i]->setPixmap(QPixmap::fromImage(*lineImage[i]).scaled (75,75));

            lineLabel[i]=new QLabel((*t)[i]->get_id());

            lineView[i]=new QPushButton("Visualizza Info");
                lineView[i]->setIcon (QIcon("GUI/Icon/icon_id_alt"));
            lineButton[i]=new QPushButton("Aggiungi ai contatti");
                lineButton[i]->setIcon (QIcon("GUI/Icon/icon_plus-alt"));
        }
        //layout sempre presente in questo punto

        //Pulisco layout.
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0){
            child->widget()->deleteLater();
            delete child;
        }
        for(int i=0;i<t->size();++i)
        {
            layout2->addWidget (lineLabelImage[i],i,0);
            layout2->addWidget (lineLabel[i],i,1);
            layout2->addWidget (lineView[i],i,3);
            layout2->addWidget (lineButton[i],i,4);

            connect(lineView[i], &QPushButton::clicked,[=]{callDrawView((*t)[i]);});
            connect(lineButton[i], &QPushButton::clicked,[=]{addUNet((*t)[i]->get_id());});
        }
    }
    else{
        QLabel* lineLabel=new QLabel("Nessun risultato");

        //Pulisco layout.
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0){
            child->widget()->deleteLater();
            delete child;
        }
        layout2->addWidget(lineLabel,0,0,0,0,Qt::AlignCenter);
     }

    QScrollArea *area = new QScrollArea(this);
    QWidget* x=new QWidget();

    area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    area->setWidget(x);
    area->setWidgetResizable (true);
    x->setLayout(layout2);

    layout->addWidget(area);
}

void homeUserView::home(){
    QLabel* lineLabel=new QLabel();
    //layout sempre presente in questo punto.
    QGridLayout* layout = dynamic_cast<QGridLayout*>(ViewGroupBox->layout ());

    //Pulisco layout
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0){
        child->widget()->deleteLater();
        delete child;
    }
          layout->addWidget (lineLabel,1,1);
}

void homeUserView::work (){}

void homeUserView::profileEdit(User* a){
    Info i=a->get_pf().idInfo;
        QLabel* lineLabel=new QLabel(a->get_id ()+(QString)"\n"+"Tipo Utente:"+
            QString::number (a->typeUser())+(QString)"\n"+
             "Nome "+i.get_name()+"\n"
                +"Cognome "+i.get_lastname()+"\n"
                    +"Mail "+i.get_mail ()+"\n"
                        +"Provenienza "+i.get_mail()+"\n"
                            +"Settore "+i.get_provenienza()+"\n"
                                +"Lavoro "+i.get_settore()+"\n"
                                    +"Lingue "+i.get_lavoro()+"\n"
                                         +"Interesse "+i.get_interessi()+"\n"
                                            +"Formazione:\n"+i.get_formazione ().QStringstamp ()+"\n"
                                                 +"\n------------------------------------------------------------------------\n");

        QPushButton* lineButton=new QPushButton("Modifica Profilo");
        lineButton->setIcon (QIcon("GUI/Icon/icon_document"));
        //layout sempre presente in questo punto.
        QGridLayout* layout = dynamic_cast<QGridLayout*>(ViewGroupBox->layout ());
        //Pulisco layout.
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0){
            child->widget()->deleteLater();
            delete child;
        }
              layout->addWidget (lineLabel,0,0);
              layout->addWidget (lineButton,1,0,Qt::AlignCenter);
              connect(lineButton, &QPushButton::clicked,this,&homeUserView::callEditProfile);
}

void homeUserView::callEditProfile(){
    i->userEditProfile();
}

void homeUserView::callViewProfile(){
    i->userViewProfile();
}

void homeUserView::addUNet(QString x){
    i->userCallAddNet (x);
}

void homeUserView::delUNet(QString x){
    i->userCallDelNet(x);
}

void homeUserView::callNet(){
    i->userCallNet();
}

void homeUserView::drawNet(QVector<User *> *n){
    QGridLayout* layout = dynamic_cast<QGridLayout*>(ViewGroupBox->layout ());
    QGridLayout* layout2 =new QGridLayout();
    if(!n->isEmpty()){
        std::cerr<<"Stampo da user";
        int Nlink=n->size ();
        QImage* lineImage[Nlink];
        QLabel* lineLabel[Nlink];
        QLabel* lineLabelImage[Nlink];
        QPushButton* lineButton[Nlink];
        QPushButton* lineView[Nlink];
        //Pulisco layout.
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0){
            child->widget()->deleteLater();
            delete child;
        }



        for(int i=0;i<n->size ();i++){
              lineImage[i]=new QImage((*n)[i]->get_pf ().ViewImage());
              lineLabel[i]=new QLabel((*n)[i]->get_pf ().idInfo.get_name ()+" "+(*n)[i]->get_pf ().idInfo.get_lastname());
              lineLabelImage[i]=new QLabel;
              lineLabelImage[i]->setPixmap(QPixmap::fromImage(*lineImage[i]).scaled (75,75));
              lineButton[i]=new QPushButton("Del");
                lineButton[i]->setIcon (QIcon("GUI/Icon/icon_trash"));
              lineView[i]=new QPushButton("Info");
                lineView[i]->setIcon (QIcon("GUI/Icon/icon_id_alt"));

              layout2->addWidget (lineLabelImage[i],i,0);
              layout2->addWidget (lineView[i],i,1);
              layout2->addWidget (lineLabel[i],i,2);
              layout2->addWidget (lineButton[i],i,3);
              connect(lineView[i], &QPushButton::clicked,[=]{callDrawViewNet((*n)[i]);});
              connect(lineButton[i], &QPushButton::clicked,[=]{QString x=(*n)[i]->get_id();delUNet(x);});
        }
    }
        else{
        QLabel* lineLabel=new QLabel("Nessun risultato1!!1");

        //Pulisco layout.
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != 0){
            child->widget()->deleteLater();
            delete child;
        }
        layout2->addWidget (lineLabel);

    }
        QScrollArea *area = new QScrollArea(this);
        QWidget* x=new QWidget();
           // Make the scroll step the same width as the fixed widgets in the grid
        area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        area->setWidget(x);
        area->setWidgetResizable (true);
        x->setLayout(layout2);

        layout->addWidget(area);

}

void homeUserView::callSearch (QVector<int> x, QVector<QString> y){
    i->search (x,y);
}
void homeUserView::callDrawView(User* u){
    i->userCallViewU(u);
}

void homeUserView::callDrawViewNet(User* u){
    i->userCallViewUNet(u);
}

void homeUserView::reloadImage(QString ind){
    QGridLayout* layout = dynamic_cast<QGridLayout*>(imageProfile->layout ());
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0){
        child->widget()->deleteLater();
        delete child;
    }
    QImage imgP;
    imgP.load(ind);
    imgProfile=new QLabel;
    imgProfile->setPixmap (QPixmap::fromImage (imgP).scaled (150,150));

    layout->addWidget (imgProfile);
}
