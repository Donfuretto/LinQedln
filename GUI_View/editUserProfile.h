#ifndef editUserProfile_H
#define editUserProfile_H
#include <QApplication>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QWidget>
#include <QMap>
#include <iostream>
#include <QMenu>
#include <QMenuBar>
#include <QGridLayout>
#include <QComboBox>
#include <QLayout>
#include <QImage>
#include <QPainter>
#include <QPicture>
#include <QDir>
#include <QScrollArea>
#include <QDesktopServices>
#include <QFileDialog>
#include "GUI_Control/controller.h"

class controller;

class EditUserProfile:public QWidget{
Q_OBJECT
public:
    EditUserProfile(Profile*, controller *);
    void setId(QString);
    void setC(controller*);
    void setView(QGroupBox*);
    void printResearch(QVector<Profile>*);
    void profileEdit(Profile*);
    void drawInfo();
    void drawWork();
    void drawForm();
    void drawEsp();
    void updateProfile(Profile*);
public slots:
    void home();
    void callEditProfile();
    void callSaveInfo();
    void callSaveWork();
    void callSaveEsp();
    void callSaveForm();
    void callChangePw();
    void callDelEsp(int);
    void callAddEsp();
    void callChangeImage();
    void showAddEsp ();
private:
    Profile* profile;
    QGridLayout* layoutHome;
    QLabel* x;
    controller* i;
    QGridLayout* mainLayout;
    QGroupBox* imageProfile;
    QGroupBox* topGroupBox;
    QGroupBox* rightGroupBox;
    QGroupBox* superTopGroupBox;
    QGroupBox* SaveBGroupBox;
    QLineEdit* lineEdits[10];
    QLabel* lineLabel[10];
    QPushButton* buttons[10];
    QLabel* imgProfile;
    QLabel* labelName;
    QString id;

    void createHomeEdit();//Pagina home
};

#endif // MYWIDGET_H
