#ifndef LOGINVIEW_H
#define LOGINVIEW_H
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

class loginView:public QWidget{
Q_OBJECT
public:
    loginView();
public slots:
    void speed(QString, QString);
private:
        QGroupBox* horizontalGroupBox;
        QGroupBox* gridGroupBox;
        QTextEdit* smallEditor;
        enum { NumGridRows = 3, NumButtons = 1 };
        QLabel* labels[NumGridRows];
        QLineEdit* lineEdits[NumGridRows];
        QPushButton* buttons[NumButtons];
    void createGridGroupBox();
    void buttonsClickOn();
    void errLogin();
    void buttonsClickOff();
    };

#endif // MYWIDGET_H
