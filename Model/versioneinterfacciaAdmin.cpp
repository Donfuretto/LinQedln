#include "versioneinterfaccia.h"
#include "versioneinterfacciaUser.cpp"

//AdminVersion
AdminVersion::AdminVersion(const QString s, const QString pw){
    Adb=DB();
    if(Adb.controlAdmin(s,pw))
        Adb.load();
    else
        ExcError("Caricamento DB",1);
}//carica db;

void AdminVersion::insert(User* u){
        Adb.insert(u);
}
void AdminVersion::reloadDb (){
    Adb.load ();
}
void AdminVersion::remove(IdLogin il){
    Adb.remove(il);
}

void AdminVersion::save(){
    Adb.save();
    ExcError("Salvataggio DB",0);
}

User *AdminVersion::find(IdLogin u){
    User* ris=Adb.find(u);
    if(ris)
        return ris;
    else{
        ExcError("Errore ricerca",1);
        return 0;
    }
}


void AdminVersion::editUserInfo (const IdLogin u,const Info& i){
    Adb.find(u)->get_pf().editInfo(i);
}

void AdminVersion::changeSubscripionType (const IdLogin idl,const int i){
    User* aU=Adb.find(idl);
    if(aU->typeUser ()==i)
        ExcError("Account Stesso tipo",0);
    else{
        User *nU=nU->createUser(aU->get_id(),aU->get_pf (),aU->get_net(),i);
        remove(aU->get_id());
        Adb.insert(nU,1);
        ExcError("Account convertito",0);
    }
    Adb.save ();
}

QString AdminVersion::get_pw (QString id) const{
    return Adb.get_Pw(id);
}

QVector<User*>* AdminVersion::research(const QVector<int> ninfo, const QVector<QString> r){
    int nfilter=r.size ();
    QVector<User*>* ris= new QVector<User*>;
    int cont=0;
    bool test=true;
    for(QMap<IdLogin,User*>::const_iterator it=Adb.get_db ()->begin(); it!=Adb.get_db()->end();++it){//Uso di iteratori constanti sul database
        while(cont<nfilter&&test){
            if(!((*it)->get_pf().idInfo.get_filtInfo(ninfo[cont]).contains(r[cont],Qt::CaseInsensitive)))
                test=false;
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
    return ris;
}

void AdminVersion::changeDb(QString i){
    Adb.load(i);
}
void AdminVersion::backupDb (QString i){
    Adb.save(i);
}
