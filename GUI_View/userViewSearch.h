#ifndef userViewSearch_H
#define userViewSearch_H
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
#include <QWidget>
#include <QGridLayout>
#include "GUI_Control/controller.h"

class userViewSearch:public QWidget{
Q_OBJECT
public:
    userViewSearch(QString);
private:
        QGroupBox* GroupBox;
        QLabel* labels;
    void createGridGroupBox(QString);
    };

#endif
