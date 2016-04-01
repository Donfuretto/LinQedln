#include "user.h"

//IdLogin
IdLogin::IdLogin(QString s): login(s) {}
QString IdLogin::getid() const{return login;}
IdLogin& IdLogin::operator=(const QString v){
    login=v;
    return *this;
}
bool IdLogin::operator<( IdLogin v) const{
    return (login<v.login);
}

bool IdLogin::operator==(const IdLogin i){
    return getid()==i.getid ();
}

bool IdLogin::operator==(const QString i){
    return getid()==i;
}


//Network
Network::Network(QVector<QString> c):net(c),Nlink(c.size()){}
Network::Network(){Nlink=0;}
void Network::add(const User* u){
    if(!net.contains (u->get_id())){
        net.push_back(u->get_id());
        Nlink++;
    }
    else
        ExcError("user già presente",0);
}
bool Network::remove (IdLogin u){
    bool fatto=false;
    for(int i=0;i<net.size();++i){
        if(net[i]==u.getid ()){
            net.removeAt (i);
            Nlink--;
            fatto=true;
        }
    }
    if(fatto==true){
        ExcError("Rimozione eseguita",0);
        return true;
    }
    else{
        ExcError("Errore Rimozione",1);
        return false;
    }
}

int Network::getlink ()const{
    return Nlink;
}

QString Network::QStringstamp(){
    int Nlink=getlink();
    if(Nlink){
        QString s="";
        for(int i=0;i<net.size();++i){
            s+=net[i]+" ";
        }
        return s;
    }
    else
        return "";
}

QVector<QString> Network::get_net () const{
    return net;
}

//User
User::User(IdLogin a, Profile p, Network *n){
    mailid=a.getid ();
    pf=p;
    network=n;
}

User* User::createUser(IdLogin userId,Profile p,Network* n,int typeAcc){
    User* pa;
    if(typeAcc==1)
        pa=new BasicUser(userId,p,n);
    else if(typeAcc==2)
        pa=new BusinessUser(userId,p,n);
    else
        pa=new ExecutiveUser(userId,p,n);

    return pa;
}

QString User::QStringstamp() const{
    return "Id "+mailid.getid ()+" "+pf.QStringstamp ()+" ";
}

//Get
QString User::get_id () const{
    return mailid.getid();
}
int User::get_Nnet () const{
    return network->getlink ();
}
Profile User::get_pf() const{
    return pf;
}
Network* User::get_net() const{
    return network;
}

QString User::get_img () const{
    return pf.ViewImage ();
}

//Basic User
int BasicUser::Nfiltri=2;
int BasicUser::NContattiV=100;
int BasicUser::NPresentazioni=5;
int BasicUser::MessaggiMail=0;

BasicUser::BasicUser(IdLogin id, Profile pf, Network *net):User(id,pf,net){}

QVector<User*>* BasicUser::research(const QVector<int>ninfo,const QVector<QString> r,const DB* dbr){
    int nfilter=r.size ();
    QVector<User*>* ris= new QVector<User*>;
    if(nfilter>Nfiltri){
        ExcError("Errori filtri ricerca",1);
        return 0;
    }
    else{
        int cont=0;
        bool test=true;
        for(QMap<IdLogin,User*>::const_iterator it=dbr->get_db()->begin(); it!=dbr->get_db()->end();++it){
            while(cont<nfilter&&test){
                if(!((*it)->get_pf().idInfo.get_filtInfo(ninfo[cont]).contains(r[cont],Qt::CaseInsensitive))){
                    test=false;}
                else
                    cont++;
            }
            test=true;
            if(cont==nfilter){
                ris->push_back((*it));
                cont=0;
            }
            else
                cont=0;
        }
    }
    return ris;
}
QString BasicUser::MyViewYou(User *u){
     QString ris;
     ris="Nome: "+u->get_pf ().idInfo.get_name()+"\n"
                     +"Cognome: "+u->get_pf ().idInfo.get_lastname()+"\n"
                       +"Lavoro: "+u->get_pf ().idInfo.get_lavoro ()+"\n";
     return ris;
}
QString BasicUser::ViewContact(User *u){
    QString ris;
    ris=u->get_pf ().QStringstamp();
    return ris;
}
int BasicUser::typeUser(){
    return 1;
}

//Bussness User
int BusinessUser::Nfiltri=4;
int BusinessUser::NContattiV=300;
int BusinessUser::NPresentazioni=15;
int BusinessUser::MessaggiMail=0;

BusinessUser::BusinessUser(IdLogin id, Profile pf, Network *net):User(id,pf,net){}

QVector<User*>* BusinessUser::research(const QVector<int>ninfo,const QVector<QString> r,const DB* dbr){
    int nfilter=r.size ();
    QVector<User*>* ris= new QVector<User*>;
    if(nfilter>Nfiltri){
        ExcError("Errori filtri ricerca",1);
        return 0;
    }
    else{
        int cont=0;
        bool test=true;
        for(QMap<IdLogin,User*>::const_iterator it=dbr->get_db()->begin(); it!=dbr->get_db()->end();++it){
            while(cont<nfilter&&test){
               if(!((*it)->get_pf().idInfo.get_filtInfo(ninfo[cont]).contains(r[cont],Qt::CaseInsensitive)))
                {
                    test=false;}
                else
                    cont++;
            }
            test=true;
            if(cont==nfilter){
                ris->push_back((*it));
                cont=0;
            }
            else
                cont=0;
        }
    }
    return ris;
}

int BusinessUser::typeUser(){
    return 2;
}

QString BusinessUser::MyViewYou(User *u){
     QString ris;
     ris=u->get_pf ().QStringstamp ();
     return ris;
}

QString BusinessUser::ViewContact(User *u){
    QString ris;
    ris=u->QStringstamp ();
    return ris;
}

//ExecutiveUser
int ExecutiveUser::Nfiltri=2;
int ExecutiveUser::NContattiV=100;
int ExecutiveUser::NPresentazioni=35;
int ExecutiveUser::MessaggiMail=0;

ExecutiveUser::ExecutiveUser(IdLogin id, Profile pf, Network *net):User(id,pf,net){}

QVector<User*>* ExecutiveUser::research(const QVector<int>ninfo,const QVector<QString> r,const DB* dbr){
    int nfilter=r.size ();
    QVector<User*>* ris= new QVector<User*>;
    if(nfilter>Nfiltri){//Se filtri superano possibilità tipo accont
        ExcError("Errori filtri ricerca",1);
        return 0;
    }
    else{
        int cont=0;
        bool test=true;
        for(QMap<IdLogin,User*>::const_iterator it=dbr->get_db()->begin(); it!=dbr->get_db()->end();++it){//Uso di iteratori constanti sul database
            while(cont<nfilter&&test){
                if(!((*it)->get_pf().idInfo.get_filtInfo(ninfo[cont]).contains(r[cont],Qt::CaseInsensitive)))
                {
                    test=false;}
                else
                    cont++;
            }
            test=true;
            if(cont==nfilter){
                ris->push_back((*it));
                cont=0;
            }
            else
                cont=0;
        }
    }
    return ris;
}

QString ExecutiveUser::MyViewYou(User *u){
     QString ris;
     ris=u->get_pf ().QStringstamp ()+"\n"+u->get_net()->QStringstamp();
     return ris;
}
QString ExecutiveUser::ViewContact(User *u){
    QString ris;
    ris=u->QStringstamp ();
    return ris;
}
int ExecutiveUser::typeUser(){
    return 3;
}

//Smart pointer.
    SmartUser::SmartUser(User* user):u(user){}
    SmartUser::SmartUser(const SmartUser& Suser):u(Suser.u){}
    SmartUser::~SmartUser(){delete u;}
    User* SmartUser::operator->() const{ return u;}
    User& SmartUser::operator*() const{return *u;}
    SmartUser& SmartUser::operator=(const SmartUser x){
        if(this!=&x)
            this->u=x.u;
    return *this;
    }
