#ifndef USER_H
#define USER_H
#include <QMap>
#include <QString>
#include <QVector>
#include <QTextStream>
#include "profilo.h"
#include "database.h"

class DB;

class IdLogin {
    QString login;
public:
    IdLogin(QString ="");
    IdLogin& operator=(const QString);
    bool operator==(const IdLogin);
    bool operator==(const QString);
    bool operator<(IdLogin) const;
    QString getid() const;
};
std::ostream& operator<<(std::ostream&,const IdLogin&);


class User;

class Network{
    int Nlink;
    QVector<QString> net;
public:
    Network();
    void add(const User* u);
    bool remove(IdLogin u);
    void ViewNet();
    int getlink() const;
    QVector<QString> get_net() const;
    Network(QVector<QString>);
    QString QStringstamp();
};



class User{
public:
    Profile pf;
    Network *network;
    IdLogin mailid;

    User(IdLogin,Profile,Network*);
    User* createUser(IdLogin,Profile,Network*,int);

    //Get
    Profile get_pf() const;
    Network* get_net() const;
    QString get_id() const;

    QString get_img() const;
    QString QStringstamp() const;
    int get_Nnet() const;
    virtual QVector<User*>* research(const QVector<int> ninfo, const QVector<QString>, const DB*) =0;
    virtual int typeUser() =0;
    virtual QString ViewContact(User*) =0;
    //ricerca
    virtual QString MyViewYou(User*) =0;
    virtual ~User(){}
};
std::ostream& operator<<(std::ostream&,const User&);

class BasicUser: public User {

protected:
    static int Nfiltri;
    static int NContattiV;
    static int NPresentazioni;
    static int MessaggiMail;
public:
    BasicUser(IdLogin,Profile,Network* =0);
    virtual QVector<User*> *research(const QVector<int> ninfo, const QVector<QString>, const DB*);
    virtual QString MyViewYou (User*);
    virtual QString ViewContact(User*);
    virtual int typeUser();
};

class BusinessUser: public User {

protected:
    static int Nfiltri;
    static int NContattiV;
    static int NPresentazioni;
    static int MessaggiMail;
public:
    BusinessUser(IdLogin,Profile,Network*);
    virtual QString MyViewYou (User*);
    virtual QString ViewContact(User*);
    virtual QVector<User*> *research(const QVector<int> ninfo, const QVector<QString>, const DB*);
    virtual int typeUser();
};

class ExecutiveUser: public User {
protected:
    static int Nfiltri;
    static int NContattiV;
    static int NPresentazioni;
    static int MessaggiMail;
public:
    ExecutiveUser(IdLogin,Profile,Network*);
    virtual QVector<User*> *research(const QVector<int> ninfo, const QVector<QString>, const DB*);
    virtual QString MyViewYou (User*);
    virtual QString ViewContact(User*);
    virtual int typeUser();
};


class SmartUser{
private:
    User* u;
public:
    SmartUser(User*);
    SmartUser(const SmartUser&);
    ~SmartUser();
    User* operator->() const;
    User& operator*() const;
    SmartUser& operator=(const SmartUser x);
};

#endif
