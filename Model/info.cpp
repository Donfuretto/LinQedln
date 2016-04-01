#include "info.h"
#include <QString>
#include <QMap>
#include <QVector>


//Esperienza
Esperienza::Esperienza(QString n, QString t, QString l, QString p):
                       nomeazienda(n),titolo(t),localita(l),periodo(p){}

Esperienza::Esperienza(const Esperienza& e){
    if(this!=&e){
        nomeazienda=e.nomeazienda;
        titolo=e.titolo;
        localita=e.localita;
        periodo=e.periodo;
    }
}
Esperienza& Esperienza::operator=(const Esperienza& e){
    if(this!=&e){
        nomeazienda=e.nomeazienda;
        titolo=e.titolo;
        localita=e.localita;
        periodo=e.periodo;
    }
    return *this;
}
void Esperienza::edit (const Esperienza& e){
    if(nomeazienda!=e.nomeazienda&&!e.nomeazienda.isEmpty())
        nomeazienda=e.nomeazienda;
    if(titolo!=e.titolo&&!e.titolo.isEmpty())
        titolo=e.titolo;
    if(localita!=e.localita&&!e.localita.isEmpty())
        localita=e.localita;
    if(periodo!=e.periodo&&!e.periodo.isEmpty())
        periodo=e.periodo;
}

QString Esperienza::QStringstampE() const{
return nomeazienda+" "
        +titolo+" "
            +localita+" "
                +periodo+"\n";
}

//get Esp
QString Esperienza::get_nomeazienda() const{
    return nomeazienda;
}
QString Esperienza::get_titolo() const{
    return titolo;
}
QString Esperienza::get_localita() const{
    return localita;
}
QString Esperienza::get_periodo() const{
    return periodo;
}
QVector<Esperienza> Info::get_esperienze() const{
    return esperienze;
}

//Formazione
Formazione::Formazione(QString t, QString s, QString v, QString a, QString d, QString r):
                       title(t),sector(s),valutation(v),activity(a),descriction(d),award(r) {}

Formazione::Formazione(const Formazione& f){
    if(this!=&f){
        title=f.title;
        sector=f.sector;
        valutation=f.valutation;
        activity=f.activity;
        descriction=f.descriction;
        award=f.award;
    }
}

bool Formazione::is_Empty() const{
    return (title.isEmpty()&&sector.isEmpty()&&valutation.isEmpty()&&
                activity.isEmpty()&&descriction.isEmpty()&&award.isEmpty());
}
Formazione& Formazione::operator=(const Formazione& x){
    if(this!=&x){
        title=x.title;
        sector=x.sector;
        valutation=x.valutation;
        activity=x.activity;
        descriction=x.descriction;
        award=x.award;
    }
    return *this;
}

void Formazione::set_title (const QString x){title=x;}
void Formazione::set_sector (const QString x){sector=x;}
void Formazione::set_valutation (const QString x){valutation=x;}
void Formazione::set_activity (const QString x){activity=x;}
void Formazione::set_descriction (const QString x){descriction=x;}
void Formazione::set_award (const QString x){award=x;}

QString Formazione::get_title() const{return title;}
QString Formazione::get_sector() const{return sector;}
QString Formazione::get_valutation() const{return valutation;}
QString Formazione::get_activity() const{return activity;}
QString Formazione::get_descriction() const{return descriction;}
QString Formazione::get_award() const{return award;}

void Formazione::edit_form (const Formazione & x){
    if (!x.is_Empty()){
        if(title!=x.title)
            title=x.title;
        if(sector!=x.sector)
            sector=x.sector;
        if(valutation!=x.valutation)
            valutation=x.valutation;
        if(activity!=x.activity)
            activity=x.activity;
        if(descriction!=x.descriction)
            descriction=x.descriction;
        if(award!=x.award)
            award=x.award;
    }
    else
        ExcError("nessuna modifica richiesta a formazione",0);
}

QString Formazione::QStringstamp() const{
return title+" "
        +sector+" "
        +valutation+" "
        +activity+" "
        +descriction+" "
        +award;
}

//Info
Info::Info(QString n, QString l, QString m, QString p, QString s,
           QString la, QString li, QString in)
     :name(n),lastname(l),mail(m),provenienza(p),settore(s),lavoro(la),
       lingue(li),interessi(in){}

Info& Info::operator=(int i){
    name=i;
    lastname=i;
    mail=i;
    return *this;
}

void Info::setEsp(const QVector<Esperienza> e){
    for(int i=0;i<e.size ();++i){
        esperienze.push_back (e[i]);}
}
//Remove e Add
void Info::addesp(const Esperienza e){
    esperienze.push_back(e);
    ExcError("Agginta esperienza",0);
}
void Info::delesp(const int i){
    if(esperienze.size()<i)
        ExcError("Errore indice fuori da esperienza",1);
    else
        esperienze.remove(i);
}
void Info::editEsp(const Esperienza& e,const int i){
    esperienze[i].edit(e);
}

void Info::editEsp(const QVector<Esperienza> e){
    if(esperienze.size()==e.size())
        for(int i=0;i<esperienze.size();i++)
            esperienze[i].edit(e[i]);
    else
        ExcError("Nessuna modifica a esp",0);
}
void Info::setFormazione(const Formazione x){
    formazione=x;
}

void Info::set_name (const QString x){name=x;}
void Info::set_lastname (const QString x){lastname=x;}
void Info::set_mail (const QString x){mail=x;}
void Info::set_provenienza (const QString x){provenienza=x;}
void Info::set_settore (const QString x){settore=x;}
void Info::set_lavoro (const QString x){lavoro=x;}
void Info::set_lingue (const QString x){lingue=x;}
void Info::set_interessi (const QString x){interessi=x;}
void Info::set_formazione (const Formazione x){formazione.edit_form (x);}

QString Info::get_name () const{return name;}
QString Info::get_lastname () const{return lastname;}
QString Info::get_mail () const{return mail;}
QString Info::get_provenienza () const{return provenienza;}
QString Info::get_settore () const{return settore;}
QString Info::get_lavoro () const{return lavoro;}
QString Info::get_lingue () const{return lingue;}
Formazione Info::get_formazione() const{return formazione;}
QString Info::get_interessi() const{return interessi;}
//filtro info

QString Info::get_filtInfo (const int Nfilter) const{
        switch(Nfilter){
            case(0):
                return name;
            case(1):
                return lastname;
            case(2):
                return provenienza;
            case(3):
                return settore;
            case(4):
                return lavoro;
            case(5):
                return lingue;
            case(6):
                return mail;
            default:
                ExcError("Errore Info non disponibile",1);
        }
        return 0;
}

//edit
void Info::edit (const Info & i){
    if(name!=i.name&&!i.name.isEmpty())
        name=i.name;
    if(lastname!=i.lastname&&!i.lastname.isEmpty())
        lastname=i.lastname;
    if(mail!=i.mail&&!i.mail.isEmpty())
        mail=i.mail;
    if(provenienza!=i.provenienza&&!i.provenienza.isEmpty())
        provenienza=i.provenienza;
    if(settore!=i.settore&&!i.settore.isEmpty())
        settore=i.settore;
    if(lavoro!=i.lavoro&&!i.lavoro.isEmpty())
        lavoro=i.lavoro;
    if(lingue!=i.lingue&&!i.lingue.isEmpty())
        lingue=i.lingue;
    if(interessi!=i.interessi&&!i.interessi.isEmpty())
        interessi=i.interessi;

    editEsp(i.esperienze);
    formazione.edit_form(i.formazione);
}
QString Info::view_formazione() const{return formazione.QStringstamp();}
//Stampa Vettore di esperienze

QString Info::Espstampa() const{
    QString ris="";
    for(int i=0;i<esperienze.size();++i){
        ris+=esperienze[i].QStringstampE();
    }
    return ris;
}

QString Info::QStringstamp() const{
    return "Nome "+name
            +" Cognome "+lastname
            +" Mail "+mail
            +" Provenienza "+provenienza
            +" Settore "+settore
            +" Lavoro "+lavoro
            +" \nInteresse\n"+interessi
            +"\nLingue\n"+lingue
            +"\nFormazione\n"
            +formazione.QStringstamp()
            +"\nEsperienze: \n"
            +Espstampa();
}
