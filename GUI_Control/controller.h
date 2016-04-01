#ifndef controller_H
#define controller_H
#include "GUI_View/loginView.h"
#include "GUI_View/HomeAdminView.h"
#include "GUI_View/HomeUserView.h"
#include "GUI_View/editUserProfile.h"
#include "GUI_View/userViewSearch.h"
#include "Model/versioneinterfaccia.h"

#include "Model/excerror.h"

class homeAdminView;
class homeUserView;
class EditUserProfile;
class userViewSearch;

class controller{
private:
    DB* dataBase;
    loginView *lv;
    AdminVersion* A;
    UserVersion* U;
    userViewSearch* uVs;
    homeAdminView* adminV;
    homeUserView* userV;
    EditUserProfile* editProfile;
public:
    controller();
    void Start();
    int viewLogin();
    //Admin
    void adminAdd(bool, QString, int);
    void adminDel(bool, QString);
    void adminEdit(bool, QString);
    void adminChangeT(bool, QString, int);
    void adminSearch(QVector<int>, QVector<QString>);
    void adminChangeDb(QString);
    void adminBackupDb(QString);
    //Miste
    void search(QVector<int>, QVector<QString>);
    bool enter(QString,QString);
    //User
    void userCallWork();
    void userCallNet();
    void userCallUpImage(QString);
    void userCallAddNet(QString);
    void userCallDelNet(QString);
    void userCallViewUNet(User*);
    void userCallViewU(User*);
    void userCallChangePw();
    void userEditProfile();
    void userViewProfile();
    //EditProfile
    void editProfileCallHome();
    void userSaveInfo(QVector<QString>);
    void userSaveWork(QVector<QString>);
    void userSaveForm(QVector<QString>);
    void userNewEsp(QVector<QString>);
    void userDelEsp(int);
};
#endif
