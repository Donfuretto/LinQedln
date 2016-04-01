#ifndef HOMEUSERVIEW_H
#define HOMEUSERVIEW_H
#include <QApplication>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMap>
#include <iostream>
#include <QMenu>
#include <QMenuBar>
#include <QImage>
#include <QPainter>
#include "GUI_Control/controller.h"
#include "Model/user.h"
class controller;

class homeUserView:public QWidget{
Q_OBJECT
public:
    homeUserView(QString, QString);
    void setId(QString);
    void setC(controller*);
    void setView(QGroupBox*);
    void printResearch(QVector<User*>*);
    void profileEdit(User *a);
    void drawNet(QVector<User *>*);
    void reloadImage(QString);

public slots:
    void home();
    void addUNet(QString);
    void delUNet(QString);
    void callEditProfile();
    void callViewProfile();
    void callDrawView(User*);
    void callDrawViewNet(User*);
    void callNet();
    void work();
    void callSearch(QVector<int>,QVector<QString>);
private:
    QGridLayout* layoutHome;
    QString linkImage;
    QLabel* x;
    controller* i;
    QGroupBox* imageProfile;
    QGroupBox* leftGroupBox;
    QGroupBox* rightGroupBox;
    QGroupBox* ViewGroupBox;
    QLineEdit* lineEdits[1];
    QPushButton* buttons[5];
    QPushButton* editB;
    QLabel* imgProfile;
    QLabel* labelName;
    QString id;

    void createHomeUser();
    void createNetPage();
    void createEditPage(QString);
    void createWorkPage();

};

#endif // MYWIDGET_H
