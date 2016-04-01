#include <QApplication>
#include "iostream"
#include "Model/versioneinterfaccia.h"
#include "GUI_Control/controller.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   controller x;
   x.Start();
   return app.exec();
}

