#ifndef INFO_H
#define INFO_H
#include <QString>
#include <QMap>
#include <QVector>
#include <Model/excerror.h>

class Esperienza{
private:
    QString nomeazienda;
    QString titolo;
    QString localita;
    QString periodo;
public:
    Esperienza(QString ="",QString ="", QString ="",QString ="");
    Esperienza(const Esperienza&);
    Esperienza& operator=(const Esperienza&);
    QString QStringstampE() const;
    void edit(const Esperienza&);
    //Get
    QString get_nomeazienda() const;
    QString get_titolo() const;
    QString get_localita() const;
    QString get_periodo() const;
};
std::ostream& operator<<(std::ostream&,const Esperienza&);

class Formazione{
private:
    QString title;
    QString sector;
    QString valutation;
    QString activity;
    QString descriction;
    QString award;
public:
    Formazione(QString ="",QString ="",QString ="",QString ="",QString ="",QString ="");
    Formazione(const Formazione&);
    Formazione& operator=(const Formazione&);

    QString QStringstamp() const;
    bool is_Empty() const;
    void set_title(const QString);
    void set_sector(const QString);
    void set_valutation(const QString);
    void set_activity(const QString);
    void set_descriction(const QString);
    void set_award(const QString);

    QString get_title() const;
    QString get_sector() const;
    QString get_valutation() const;
    QString get_activity() const;
    QString get_descriction() const;
    QString get_award() const;

    void edit_form(const Formazione&);
};
std::ostream& operator<<(std::ostream&,const Formazione&);

class Profile;

class Info {
    friend class Profile;
private:
    QString name;
    QString lastname;
    QString mail;
    QString provenienza;
    QString settore;
    QString lavoro;
    QString lingue;
    QString interessi;
    Formazione formazione;
    QVector<Esperienza> esperienze;
public:
    Info(QString ="",QString ="",QString ="",QString ="",QString ="",
                                    QString ="",QString ="",QString ="");
    Info& operator=(int);

    //funzioni Esp
    void delesp(const int);
    void addesp(const Esperienza);
    void editEsp(const QVector<Esperienza>);
    void editEsp(const Esperienza&,const int);

    //Edit
    void edit(const Info&);
    //Set
    void setFormazione(const Formazione);
    void setEsp(const QVector<Esperienza> esperienze);
    void set_name(const QString);
    void set_lastname(const QString);
    void set_mail(const QString);
    void set_provenienza(const QString);
    void set_settore(const QString);
    void set_lavoro(const QString);
    void set_lingue(const QString);
    void set_interessi(const QString);
    void set_formazione (const Formazione);

    //Get
    QString get_name()const;
    QString get_lastname()const;
    QString get_mail()const;
    QString get_provenienza()const;
    QString get_settore()const;
    QString get_lavoro()const;
    QString get_lingue()const;
    QString get_interessi()const;
    QString get_filtInfo(const int) const;
    Formazione get_formazione()const;
    QVector<Esperienza> get_esperienze()const;

    //View
    QString view_formazione()const;
    QString QStringstamp() const;
    QString Espstampa() const;
};
std::ostream& operator<<(std::ostream&,const Info&);

#endif // INFO_H
