#include <Model/versioneinterfaccia.h>

//User
UserVersion::UserVersion(IdLogin id,QString pw){
    udb=DB();
    if(udb.controlPw(id.getid (),pw)){
        udb.load();
        u=udb.find(id);
    }
    else
        ExcError("Errore login User",1);
}

void UserVersion::updateImage(const QString l){
    u->pf.SetImage(l);
    udb.save();
}
void UserVersion::updateProfile (const Info i){
       u->pf.editInfo(i);
       udb.save();
}
void UserVersion::insertRete(const User* un){
    u->get_net()->add(un);
    udb.save();
}
void UserVersion::removeRete(IdLogin un){
     if(u->get_net ()->remove(un))
     udb.save();
}
User* UserVersion::find (IdLogin x){
    return udb.find (x);
}

QVector<User*>* UserVersion::research (const QVector<int> f, const QVector<QString> rd){
    QVector<User*>* x=u->research(f,rd,&udb);
    return x;
}

int UserVersion::typeUser(){
    return u->typeUser ();
}

Profile* UserVersion::getMyProfile(){
    if(!u)
        return 0;
    Profile* k=new Profile();
    *k=u->get_pf();
    return k;
}

Network* UserVersion::getMyNet(){
    Network* n=new Network();
    n=u->get_net ();
    return n;
}

User* UserVersion::getMyUserInfo () const{
    return u;
}

void UserVersion::addEsp (Esperienza e){
    u->pf.idInfo.addesp(e);
    udb.save();
}

void UserVersion::delEsp (int i){
    u->pf.idInfo.delesp (i);
    udb.save ();
}

QString UserVersion::viewUserInfo(User* t){
    return u->MyViewYou(t);
}

QString UserVersion::viewUserInfoUnet(User* u){
    return u->ViewContact(u);
}

bool UserVersion::control() const{
    if(u)
        return true;
    else
        return false;
}
