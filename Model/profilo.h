#ifndef PROFILO_H
#define PROFILO_H
#include <QString>
#include <QMap>
#include <QVector>
#include "info.h"

class Profile{
public:

    QString image;
    Info idInfo;
    Profile();
    Profile(Info);//NO INLINE
    Profile& operator=(const Profile&);

    void editProfile(const int,QString);
    void editProfile(const Formazione);
    void editProfile(const Esperienza);

    void editInfo(const Info&);
    void setInfo(const Info);

    void viewProfile() const;
    void SetImage(QString);

    QString ViewImage() const;
    QString QStringstamp() const;
};
#endif // PROFILO_H
