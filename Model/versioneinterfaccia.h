#ifndef VERSIONEINTERFACCIA_H
#define VERSIONEINTERFACCIA_H
#include <QMap>
#include "database.h"

class AdminVersion:public DB{
private:
    DB Adb;
public:
    AdminVersion(const QString,const QString);
    void reloadDb();
    void changeDb(QString);
    void backupDb(QString);
    void save();
    void insert(User* u);
    User* find(IdLogin);//Ricerca per IdLogin direttamente su Qmap db
    void remove(IdLogin);
    QString viewdb () const;
    QString get_pw(QString) const;
    void editUserInfo(const IdLogin,const Info&);
    QVector<User*> *research(const QVector<int>,const QVector<QString>);
    void changeSubscripionType(const IdLogin,const int);
};

class UserVersion:public DB{
private:
    User* u;
    DB udb;
public:
    UserVersion(IdLogin, QString pw);
    Profile* getMyProfile();
    Network* getMyNet();
    User* getMyUserInfo() const;
    User* find(IdLogin);
    void updateImage(const QString);
    void updateProfile(const Info);
    void insertRete(const User*);
    QString viewUserInfo(User*);
    QString viewUserInfoUnet(User*);
    void removeRete(IdLogin);
    void addEsp(Esperienza);
    void delEsp(int);
    bool control() const;
    int typeUser();
    QVector<User*> *research(const QVector<int>,const QVector<QString>);
};

#endif // VERSIONEINTERFACCIA_H
