#ifndef HOMEADMINVIEW_H
#define HOMEADMINVIEW_H
#include <QApplication>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMap>
#include <iostream>
#include <QMenu>
#include <QMenuBar>
#include <QImage>
#include <QPainter>
#include <QInputDialog>
#include "Model/user.h"
#include "GUI_Control/controller.h"

class controller;

class homeAdminView:public QWidget{
Q_OBJECT
public:
    homeAdminView(QString);
    void setId(QString);
    void setC(controller*);
    void setView(QGroupBox*);
    void printResearch(QVector<User*>* t);
public slots:
    void addU();
    void delU();
    void cancheT();
    void editU();
    void callSearch(QVector<int>,QVector<QString>);
    void callChangeDb();
    void callBackUpDb();
private:
    controller* i;
    QGroupBox* leftGroupBox;
    QGroupBox* rightGroupBox;
    QGroupBox* TopGroupBox;
    QTextEdit* researchText;
    QLineEdit* lineEdits[1];
    QPushButton* buttons[10];
    QLabel* labelName;
    QString id;
    void createGridGroupBox();
    };

#endif // MYWIDGET_H
