#include "database.h"
#include "user.h"
#include <QFile>
#include <QDomComment>
#include <QtXml>
#include <QTime>
#include <QTextStream>
#include "versioneinterfaccia.h"
//DB
DB::DB() {}

void DB::load(QString s){
        if(s.isEmpty ())
            s="dataBase/dataBase.xml";
        QFile file(s);
        QDomDocument xml;
        if(!file.open(QIODevice::ReadOnly)){
            ExcError("Errore file database.xml",1);
        }
        xml.setContent(&file);
        QDomElement root=xml.documentElement();
        file.close();

        //Leggo dal file
        QDomElement doc=root.firstChild().toElement();
        bool found=false;
        //Variable
        QString name;
        QString userId;//mail e ID
        int typeAcc;
        QString lastname,prov,set,lav,ling,inte,Img;
        QString formT,formS,formV,formA,formD,formP;
        QString net, nNet;
        QString espA,espT,espL,espP;
        QVector<Esperienza> vEsp;
        // Loop fino a che ci sono figli
        while(!doc.isNull()&&!found){
            // cerco nome utente nel doc
            if (doc.tagName()=="USER"){
                //prelevo attributo id per utente
                userId=doc.attribute("UID","Error id found! load");
                typeAcc=doc.attribute("TYPEA","Error type! load").toInt ();
                // Prelevo il primo figlio
                QDomElement child=doc.firstChild().toElement();

                //Leggo figli user
                while (!child.isNull()){
                    //operazioni su figli
                     if (child.tagName()=="PINFO"){
                        Img=child.attribute ("IMG","--");
                        name=child.attribute("NAME","--");
                        lastname=child.attribute("LNAME","--");
                        prov=child.attribute("PROV","--");
                        set=child.attribute("SET","--");
                        lav=child.attribute("LAV","--");
                        ling=child.attribute("LING","--");
                        inte=child.attribute("INTE","--");
                     }
                     if (child.tagName()=="FORMAZIONE"){
                         formT=child.attribute("TITLE","--");
                         formS=child.attribute("SECTOR","--");
                         formV=child.attribute("VALUTATION","--");
                         formA=child.attribute("ACTIVITY","--");
                         formD=child.attribute("DESCRICTION","--");
                         formP=child.attribute("AWARD","--");
                        }
                     if (child.tagName()=="ESPERIENZE"){
                         QDomNodeList list = child.childNodes();
                     for(int i=0;i<list.size();++i){
                            espA=list.at(i).toElement ().attribute("AZIENDA","--");
                            espT=list.at(i).toElement ().attribute("TITOLO","--");
                            espL=list.at(i).toElement ().attribute("LOCALITA","--");
                            espP=list.at(i).toElement ().attribute("PERIODO","--");
                            vEsp.push_back(Esperienza(espA,espT,espL,espP));
                         }
                     }
                     if (child.tagName()=="NET")
                        nNet=child.attribute("NCONTACT","--");
                     net=child.attribute("CONTACT","--");

                child = child.nextSibling().toElement();//prossimo!
                }
                Info x(name,lastname,userId,prov,set,lav,ling,inte);
                Formazione f(formT,formS,formV,formA,formD,formP);
                x.setFormazione(f);
                x.setEsp(vEsp);
                vEsp.clear();
                Profile p(x);
                p.SetImage(Img);
                //Converto net stringa in vector
                QVector<QString> Vnet;
                    for(int i=0;i<nNet.toInt ();++i){
                        Vnet.append(net.section(" ",i,i));
                    }
                Network *n=new Network(Vnet);

                //Creo account in base al tipo:
                User* pa=pa->createUser(userId,p,n,typeAcc);
                db.insert(userId,pa);
            }//end if tag==doc
            doc = doc.nextSibling().toElement();
        }
}


void DB::save (QString s) const{
    //Creo nuovo file
    QString percorso;
    if(s.isEmpty())
        percorso="dataBase/dataBase.xml";
    else
        percorso=s;

    QFile file(percorso);
    if(!file.open(QIODevice::ReadWrite)){
        ExcError("Errore file database.xml",1);
    }
    file.resize(0);
    QDomDocument database;
    //radice unica
    QDomElement root=database.createElement("root");
    database.appendChild (root);

    QTextStream out(&file);
    //Pre ogni map della Qmap db scrivo un User

    QMap<IdLogin,User*>::ConstIterator it=db.begin();

    for(;it!=db.end();it++){
        QString temp=(*it)->QStringstamp();
        QDomElement user=database.createElement ("USER");
            user.setAttribute("UID",temp.section(" ",1,1));
            user.setAttribute("TYPEA",(*it)->typeUser());

                QDomElement nome=database.createElement("PINFO");
                    nome.setAttribute ("IMG",(*it)->get_pf ().ViewImage());
                    nome.setAttribute("NAME",temp.section(" ",3,3));
                    nome.setAttribute("LNAME",temp.section(" ",5,5));
                    nome.setAttribute("MAIL",temp.section(" ",7,7));
                    nome.setAttribute("PROV",temp.section(" ",9,9));
                    nome.setAttribute("SET",temp.section(" ",11,11));
                    nome.setAttribute("LAV",temp.section(" ",13,13));
                    nome.setAttribute("INTE",temp.section("\n",2,2));
                    nome.setAttribute("LING",temp.section("\n",4,4));
                user.appendChild(nome);

                QDomElement formazione=database.createElement("FORMAZIONE");
                    QString divform=temp.section("\n",6,6);
                    formazione.setAttribute("TITLE",divform.section (" ",0,0));
                    formazione.setAttribute("SECTOR",divform.section (" ",1,1));
                    formazione.setAttribute("VALUTATION",divform.section (" ",2,2));
                    formazione.setAttribute("ACTIVITY",divform.section (" ",3,3));
                    formazione.setAttribute("DESCRICTION",divform.section (" ",4,4));
                    formazione.setAttribute("AWARD",divform.section (" ",5,5));
                user.appendChild(formazione);

                QDomElement esperienze=database.createElement("ESPERIENZE");
                    QString esp=temp.section ("\n",7,-1);
                    QString x="Inizio";//prendo prima sessione di ultima sessione di temp
                    int cont=1;
                    while(!(esp.section ("\n",cont+1,cont+1)).isEmpty())
                    {
                        x=" "+esp.section ("\n",cont,cont);
                        QDomElement esperienza=database.createElement("ESPERIENZA");
                        esperienza.setAttribute("AZIENDA",x.section(" ",1,1));
                        esperienza.setAttribute("TITOLO",x.section(" ",2,2));
                        esperienza.setAttribute("LOCALITA",x.section(" ",3,3));
                        esperienza.setAttribute("PERIODO",x.section(" ",4,4));
                        esperienze.appendChild (esperienza);
                        ++cont;
                    }
                user.appendChild(esperienze);

                QDomElement contatti=database.createElement("NET");
                    contatti.setAttribute ("NCONTACT",(*it)->get_net ()->getlink ());
                    contatti.setAttribute ("CONTACT",(*it)->get_net ()->QStringstamp().section ("",1,-1));
                user.appendChild(contatti);

            root.appendChild(user);
    }
    database.appendChild (root);
    out<<database.toString();
    file.close();
}
User* DB::find(IdLogin idL){
    User* a;
    QMap<IdLogin,User*>::Iterator it=db.begin();
    for(;it!=db.end();++it){
        if(idL==it.key()){
            a=(*it);
            return a;
        }
    }
    return 0;
        ExcError("Errore Ricerca",1);
}

void DB::insert(User* x,bool nopw){
    if(!db.contains(x->get_id())&&x->get_id ().contains("@")){
        db.insert(x->get_id(),x);
     if(!nopw){
        QFile file("dataBase/userDB.xml");
        QDomDocument xml;
        if(!file.open(QIODevice::ReadWrite)){
            ExcError("Errore file adminDB.xml",1);
        }
        xml.setContent(&file);

        QDomElement root=xml.documentElement();
        //Leggo dal file
        QDomElement nUser=xml.createElement("USER");
        nUser.setAttribute ("ID",x->get_id ());
        nUser.setAttribute ("PW","test");
        xml.appendChild (root);
        root.appendChild(nUser);
        file.resize (0);
        QTextStream stream( &file );
        stream << xml.toString();
        file.close ();
    }
     }
    else
      ExcError("Errore inserimento",1);
}


void DB::remove(const IdLogin x){
    if(db.remove(x)){
        ExcError("Eliminato",0);
    }
    else
        ExcError("Non Eliminato",1);
}
const QMap<IdLogin,User*>* DB::get_db()const {
    return &db;
}


bool DB::controlAdmin(const QString s,const QString pw) const{
    QFile file("dataBase/adminDB.xml");
    QDomDocument xml;
    if(!file.open(QIODevice::ReadOnly)){
        ExcError("Errore file adminDB.xml",1);
    }
    xml.setContent(&file);
    QDomElement root=xml.documentElement();
    file.close();
    //Leggo dal file
    QDomElement doc=root.firstChild().toElement();
    // Loop fino a che ci sono figli
    while(!doc.isNull()){
    // cerco nome utente nel doc
        if (doc.tagName()=="ADMIN"){
        //prelevo attributo id per utente
            if(doc.attribute("ID","Error id found! load")==s)
                if(doc.attribute("PW","Error id found! load")==pw)
                    return true;
        doc = doc.nextSibling().toElement();
        }
    }
    return false;
}

bool DB::controlPw(const QString u,const QString pw) const{
    QFile file("dataBase/userDB.xml");
    QDomDocument xml;
    if(!file.open(QIODevice::ReadOnly)){
        ExcError("Errore file adminDB.xml",1);
    }
    xml.setContent(&file);
    QDomElement root=xml.documentElement();
    file.close();
    QDomElement doc=root.firstChild().toElement();
    while(!doc.isNull()){
        if (doc.tagName()=="USER"){
            if(doc.attribute("ID","Error id found! load")==u)
                if(doc.attribute("PW","Error id found! load")==pw)
                    return true;
        doc = doc.nextSibling().toElement();
        }
    }
    return false;
}

void DB::changePw (const QString id,const QString newPw) const{
    QFile file("dataBase/userDB.xml");
    QDomDocument xml;
    if(!file.open(QIODevice::ReadWrite)){
        ExcError("Errore file adminDB.xml",1);
    }
    xml.setContent(&file);
    QDomElement root=xml.documentElement();
    QDomElement doc=root.firstChild().toElement();
    while(!doc.isNull()){
        if (doc.tagName()=="USER"){
            if(doc.attribute("ID","Error id found! load")==id){
                if(doc.attribute("PW","Error id found! load")!=newPw)
                    doc.setAttribute ("PW",newPw);
                else
                    ExcError("Pw uguale alla precedente",1);
            }
        doc = doc.nextSibling().toElement();
        }
    }
    file.resize (0);
    QTextStream stream( &file );
    stream << xml.toString();
    file.close();
}

QString DB::get_Pw (const QString id) const{
    QFile file("dataBase/userDB.xml");
    QDomDocument xml;
    if(!file.open(QIODevice::ReadWrite)){
        ExcError("Errore file adminDB.xml",1);
    }
    xml.setContent(&file);
    QDomElement root=xml.documentElement();
    QDomElement doc=root.firstChild().toElement();
    while(!doc.isNull()){
        if (doc.tagName()=="USER"){
            if(doc.attribute("ID","Error id found! load")==id)
               return doc.attribute("PW","Error id found! load");
        doc = doc.nextSibling().toElement();
        }
    }
    ExcError("Id non valido per recupero pw",1);
    file.close();
    return 0;
}
