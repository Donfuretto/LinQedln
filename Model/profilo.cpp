#include "profilo.h"
#include <QFile>

//Profile
Profile::Profile(Info x):idInfo(x){}
Profile::Profile(){}
Profile& Profile::operator = (const Profile& c){
    if(this!=&c){
        idInfo=c.idInfo;
        image=c.image;
    }
    return *this;
}

void Profile::editInfo(const Info& i){
    idInfo.edit(i);
}

void Profile::setInfo(const Info i){

        if(idInfo.get_name ()!=i.get_name ())
            idInfo.set_name(i.get_name());

        if(idInfo.get_lastname ()!=i.get_lastname())
            idInfo.set_lastname(i.get_lastname());

        if(idInfo.get_mail()!=i.get_mail())
            idInfo.set_mail(i.get_mail());

        if(idInfo.get_provenienza()!=i.get_provenienza())
            idInfo.set_provenienza(i.get_provenienza());

        if(idInfo.get_settore()!=i.get_settore ())
            idInfo.set_settore(i.get_settore());

        if(idInfo.get_lavoro ()!=i.get_lavoro ())
            idInfo.set_lavoro(i.get_lavoro());

        if(idInfo.get_lingue()!=i.get_lingue())
            idInfo.set_lingue(i.get_lingue());

        if(idInfo.get_interessi ()!=i.get_interessi())
            idInfo.set_interessi(i.get_interessi());

        if(idInfo.view_formazione()!=i.view_formazione())
            idInfo.set_formazione(i.get_formazione());
}

void Profile::editProfile(const Formazione n){
   idInfo.formazione.edit_form (n);
}

void Profile::SetImage(QString x){
    image=x;
}

QString Profile::ViewImage() const{
    return image;
}


QString Profile::QStringstamp () const{
    return idInfo.QStringstamp ();
}
