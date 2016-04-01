#include "controller.h"
#include <iostream>
#include <QFile>

controller::controller(){editProfile=0;A=0;userV=0;}

void controller::Start (){
    lv=new loginView();
    dataBase=new DB();
    lv->show ();
}

bool controller::enter(QString id,QString pw){
   if(id.contains("@linQed.net")){
      if(dataBase->controlAdmin(id,pw)){
            //entra in home
               A=new AdminVersion(id,pw);
               adminV =new homeAdminView(id);
               adminV->setC(this);
               adminV->show();
               return true;
         }
         else{
          return false;
         }
    }
    else{
        if(dataBase->controlPw (id,pw)){
            U=new UserVersion(id,pw);
            if(U->control()){
                userV=new homeUserView(id,U->getMyUserInfo()->get_img());
                userV->setC(this);
                userV->show();
                return true;
            }
            else
            {
            return false;
            }
        }
       else{
            return false;
        }
    }
}

void controller::adminAdd(bool ok,QString text,int text2){
        if (ok && !text.isEmpty())
         {
             Profile x;
             Network* net=new Network();
                 User* a=a->createUser(text,x,net,text2);
                 A->insert(a);

                 A->save ();
                 A->reloadDb ();
                 delete a;
                 ExcError("Aggiunto",0);
                 adminEdit(ok,text);
         }
        ExcError("Aggiunto",1);
}

void controller::adminDel(bool ok,QString text){
         if (ok && !text.isEmpty())
         {
             A->remove(text);

             A->save ();
             ExcError("Eliminato",1);
            A->reloadDb ();
         }
}

void controller::adminEdit(bool ok,QString text){
         if (ok && !text.isEmpty()){
             if(!A->get_pw(text).isNull()){
                U=new UserVersion(text,A->get_pw(text));
                if(U){
                    this->userEditProfile();}
                else
                    ExcError("Errore Creazione user in adminEdit",1);
             }
             else
                 ExcError("ID non Valido",1);
         }
}


void controller::adminChangeT(bool ok,QString text,int text2){
    if (ok&&!text.isEmpty()&&text2){
             ExcError(text+"CambioTipo",0);
             A->changeSubscripionType(text,text2);
    }
}

void controller::adminSearch(QVector<int> filter,QVector<QString> textFilter){
    A->reloadDb ();
    adminV->printResearch(A->research(filter,textFilter));
}

void controller::search(QVector<int> filter,QVector<QString> textFilter){
    userV->printResearch (U->research(filter,textFilter));
}
