#include "controller.h"

void controller::userEditProfile(){
    if(editProfile)
        editProfile->deleteLater();
    Profile* x=new Profile();
    if(U)
        x=U->getMyProfile();
    else
        x=0;
    if(x){
        editProfile=new EditUserProfile(x,this);
        editProfile->show();
    }
    else
        ExcError("Pf non trovato",1);
}

void controller::userViewProfile(){
    userV->profileEdit(U->getMyUserInfo());
}

void controller::userCallNet(){
    QVector<QString> x=U->getMyNet()->get_net();
    QVector<User*>* ris=new QVector<User*>;
    for(int i=0;i<x.size ();++i){
        std::cerr<<x[i].toStdString ();
        if(U->find(x[i]))
        ris->push_back(U->find(x[i]));
    }
    userV->drawNet(ris);
}

void controller::editProfileCallHome(){
    editProfile->deleteLater ();
    editProfile=0;
}

void controller::userCallAddNet (QString s){
    U->insertRete(U->find(s));
}
void controller::userCallDelNet(QString s){
    U->removeRete(s);
    userCallNet();
}
void controller::userSaveInfo (QVector<QString> x){
    Info i(x[0],x[1],"",x[2]);
    U->updateProfile(i);
    editProfile->updateProfile(U->getMyProfile ());
    editProfile->drawInfo ();
    ExcError("Profilo aggiornato",0);
}

void controller::userSaveWork (QVector<QString> x){
    Info i("","","","",x[3],x[0],x[2],x[1]);

    U->updateProfile(i);
    editProfile->updateProfile(U->getMyProfile ());
    editProfile->drawWork ();
    ExcError("Profilo aggiornato",0);
}

void controller::userSaveForm (QVector<QString> x){

    Formazione f(x[0],x[1],x[2],x[3],x[4],x[5]);
    Info i;
    i.set_formazione(f);
    U->updateProfile (i);
    editProfile->updateProfile(U->getMyProfile ());
    editProfile->drawForm ();
    ExcError("Profilo aggiornato",0);
}

void controller::userDelEsp (int x){
    U->delEsp(x);
    editProfile->updateProfile(U->getMyProfile ());
    editProfile->drawEsp();
}

void controller::userNewEsp (QVector<QString> s){
    U->addEsp(Esperienza((s)[0],s[1],s[2],s[3]));
    ExcError("Aggiunta Esp",0);
    editProfile->updateProfile(U->getMyProfile ());
    editProfile->drawEsp();
}

void controller::userCallUpImage(QString i){
    U->updateImage(i);
    userEditProfile();
    if(userV)
        userV->reloadImage(i);
}

void controller::adminChangeDb(QString i){
    A->changeDb(i);
    A->save ();
}
void controller::adminBackupDb(QString i){
    A->backupDb (i);
}

void controller::userCallViewU (User * u){
    if(u){
        uVs=new userViewSearch(U->viewUserInfo(u));
        uVs->show ();
    }
    else
        ExcError("Errore vista user da search",1);
}

void controller::userCallViewUNet (User * u){
    if(u){
        uVs=new userViewSearch(U->viewUserInfo(u));
        uVs->show ();
    }
    else
        ExcError("Errore vista user da Net",1);
}

void controller::userCallChangePw(){
    if(A){
        bool ok;
        QInputDialog* inputDialog = new QInputDialog();
            inputDialog->setOptions(QInputDialog::NoButtons);
            QString text =  inputDialog->getText(NULL ,"Cambia Pw utente",
                                                  "Nuova password", QLineEdit::Normal,"", &ok);
        if(ok&&!text.isEmpty ())
        U->changePw(U->getMyUserInfo()->get_id(),text);
    }
    else{
        bool ok;
        QInputDialog* inputDialog = new QInputDialog();
            inputDialog->setOptions(QInputDialog::NoButtons);
            QString text =  inputDialog->getText(NULL ,"Cambia Pw utente",
                                                  "Vecchia password", QLineEdit::Normal,"", &ok);
         QString text2;
             text2=inputDialog->getText(NULL ,"Cambia Pw utente",
                                                  "Nuova password", QLineEdit::Normal,"", &ok);
        if(ok&&!text.isEmpty())
            if(U->controlPw (U->getMyUserInfo ()->get_id(),text)){
                U->changePw(U->getMyUserInfo()->get_id(),text2);
            }
    }
}
