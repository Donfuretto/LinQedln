#include "HomeAdminView.h"
#include <QFormLayout>

homeAdminView::homeAdminView(QString i):id(i){
    createGridGroupBox();
    QGridLayout* mainLayout = new QGridLayout();

    setWindowTitle("LinQedIn-Admin: "+i);
    setWindowIcon (QIcon("GUI/Img/loqt.jpg"));
    setLayoutDirection(Qt::LeftToRight);


    QImage imageBackground;
    imageBackground.load("GUI/Img/Sfondo.jpg");

    QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(imageBackground));
    setPalette(palette);


//gestioneGroupBox
    mainLayout->addWidget(leftGroupBox,0,0,0,1);
    mainLayout->addWidget(rightGroupBox,0,1);
    mainLayout->addWidget(researchText,1,1);
    mainLayout->setColumnStretch(1,0);

    setLayout(mainLayout);
}

void homeAdminView::createGridGroupBox(){

    leftGroupBox = new QGroupBox;
    rightGroupBox= new QGroupBox;
    researchText = new QTextEdit;

    researchText->scrollBarWidgets (Qt::AlignRight);
    QGridLayout* layout2 = new QGridLayout;
    lineEdits[0] = new QLineEdit();
    layout2->addWidget(lineEdits[0], 0, 1);
    buttons[4] = new QPushButton();
    buttons[4]->setIcon (QIcon("GUI/Icon/icon_search2"));
    buttons[4]->setFixedSize (50,25);
    layout2->addWidget (buttons[4],0,0);

    QComboBox* combos=new QComboBox;
        combos->addItem("Nome");
        combos->addItem("Cogmone");
        combos->addItem("Provenienza");
        combos->addItem("Settore");
        combos->addItem("Lavoro");
        combos->addItem("Lingue");
        combos->addItem("ID-Email");
        layout2->addWidget(combos,0,2);
        layout2->setColumnStretch (0,0);

    QGridLayout* layout = new QGridLayout;
    buttons[0] = new QPushButton("Nuovo utente");
        buttons[0]->setFixedSize (150,50);
        buttons[0]->setIcon (QIcon("GUI/Icon/icon_plus_new"));
    buttons[1] = new QPushButton("Modifica utente");
        buttons[1]->setFixedSize (150,50);
        buttons[1]->setIcon (QIcon("GUI/Icon/icon_id-2_alt"));
    buttons[2] = new QPushButton("Elimina utente");
        buttons[2]->setFixedSize (150,50);
        buttons[2]->setIcon (QIcon("GUI/Icon/icon_trash"));
    buttons[3] = new QPushButton("Cambia Account");
        buttons[3]->setFixedSize (150,50);
        buttons[3]->setIcon (QIcon("GUI/Icon/icon_profile"));
    buttons[5] = new QPushButton("Backup DB");
        buttons[5]->setFixedSize (150,50);
        buttons[5]->setIcon (QIcon("GUI/Icon/icon_folder_upload"));
    buttons[6] = new QPushButton("Cambia DB");
        buttons[6]->setFixedSize (150,50);
        buttons[6]->setIcon (QIcon("GUI/Icon/icon_folder_download"));

    QImage imgP;
    imgP.load("GUI/Img/loqt.jpg");
    QLabel* imgA=new QLabel;
    imgA->setPixmap (QPixmap::fromImage (imgP).scaled (150,150));
    layout->addWidget (imgA);

    layout->addWidget(buttons[0]);
    layout->addWidget(buttons[1]);
    layout->addWidget(buttons[2]);
    layout->addWidget(buttons[3]);
    layout->addWidget(buttons[5]);
    layout->addWidget(buttons[6]);

    QGridLayout* layoutTop=new QGridLayout;

    labelName= new QLabel(id);
    layoutTop->addWidget (labelName);

    connect(buttons[0], &QPushButton::clicked,this,&homeAdminView::addU);
    connect(buttons[2], &QPushButton::clicked,this,&homeAdminView::delU);
    connect(buttons[1], &QPushButton::clicked,this,&homeAdminView::editU);
    connect(buttons[3], &QPushButton::clicked,this,&homeAdminView::cancheT);
    connect(buttons[5], &QPushButton::clicked,this,&homeAdminView::callBackUpDb);
    connect(buttons[6], &QPushButton::clicked,this,&homeAdminView::callChangeDb);
    connect(buttons[4], &QPushButton::clicked,[=]{
        QVector<int> x;
        x.push_back(combos->currentIndex());
        QVector<QString> y;
        y.push_back(lineEdits[0]->text());
        callSearch(x,y);});


    leftGroupBox->setLayout(layout);
    rightGroupBox->setLayout(layout2);
    researchText->setText("-Login come amministratore-");

//modifiche widget
    setGeometry(500,250,600,400);
    setFixedSize (1000,500);
}
void homeAdminView::setId (QString i){
    id=i;
}
void homeAdminView::setC (controller * x){//setto controller
    i=x;
}
void homeAdminView::addU(){
    bool ok;
    QInputDialog* inputDialog = new QInputDialog();
        inputDialog->setOptions(QInputDialog::NoButtons);
        QString text =  inputDialog->getText(NULL ,"Crea nuovo utente",
                                              "Id utente(Email):", QLineEdit::Normal,"", &ok);
        int text2;
        if(ok)
            text2 =  inputDialog->getInt(NULL,"Livello Account","(1 basic, 2 bussiness, 3 ExecutiveUser)", QLineEdit::Normal,1,3,1,&ok);
         i->adminAdd(ok,text,text2);
}

void homeAdminView::delU(){
    bool ok;
    QInputDialog* inputDialog = new QInputDialog();
        inputDialog->setOptions(QInputDialog::NoButtons);
        QString text =  inputDialog->getText(NULL ,"Elimina utente",
                                              "Id utente da eliminare", QLineEdit::Normal,"", &ok);
    i->adminDel(ok,text);
}

void homeAdminView::editU (){
    bool ok;
    QInputDialog* inputDialog = new QInputDialog();
        inputDialog->setOptions(QInputDialog::NoButtons);
        QString text =  inputDialog->getText(NULL ,"Modifica info utente",
                                              "Id utente:", QLineEdit::Normal,"", &ok);
    i->adminEdit(ok,text);
}

void homeAdminView::cancheT (){
    bool ok;
    QInputDialog* inputDialog = new QInputDialog();
        inputDialog->setOptions(QInputDialog::NoButtons);
        QString text =  inputDialog->getText(NULL ,"Cambia tipologia account",
                                              "Id utente:", QLineEdit::Normal,"", &ok);
        int text2 =  inputDialog->getInt(NULL,"Livello account","Nuovo livello account(1 basic, 2 bussiness, 3 ExecutiveUser)", QLineEdit::Normal,1,3,1,&ok);
        i->adminChangeT (ok,text,text2);
}

void homeAdminView::callSearch (QVector<int> x, QVector<QString> y){
    i->adminSearch(x,y);
}

//Resarch come user.
void homeAdminView::printResearch(QVector<User*>* t){
        QString s;
        if(t){
            for(int i=0;i<t->size();i++)
            {
                s+=((*t)[i]->get_id()+(QString)"\n"+"Tipo Utente:"+
                    QString::number ((*t)[i]->typeUser())+(QString)"\n"+
                    (*t)[i]->get_pf().QStringstamp ()+
                    "\n-------------------------\n");
            }
            researchText->setText(s);
        }
        else{
            researchText->setText ("Nessuna Corispondenza");
        }
}

void homeAdminView::callChangeDb(){
    QString text= QFileDialog::getOpenFileName(
                            this,
                            "Seleziona db",
                            "/dataBase/",
                            "XML files (*.xml)");
         if (!text.isEmpty()){
             i->adminChangeDb(text);
         }
}

void homeAdminView::callBackUpDb(){
    QString text = QFileDialog::getSaveFileName(this, tr("Salva File"),
                               "/dataBase/BackUp",
                               tr("XML files (*.xml)"));
         if (!text.isEmpty()){
             std::cerr<<"Test"<<text.toStdString();
             i->adminBackupDb(text);
         }
}

