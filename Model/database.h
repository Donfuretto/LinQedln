#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>
#include "user.h"
#include "profilo.h"
#include "excerror.h"

class AdminVersion;
class IdLogin;
class User;

class DB{
private:
    QMap<IdLogin,User*> db;
public:
    DB();
    void load(QString ="");
    void save(QString ="") const;
    bool controlAdmin(const QString,const QString) const;
    bool controlPw(const QString,const QString) const;
    void changePw(const QString, const QString) const;
    void insert(User *,bool =0);
    void remove(const IdLogin);
    QString get_Pw(const QString) const;
    User* find(IdLogin);

    const QMap<IdLogin,User*> *get_db() const;
};

#endif
