#include "excerror.h"

ExcError::ExcError(QString msg,int type){
    if(type)
        std::cerr<<"err "<<msg.toStdString ();
    else
        std::cout<<"notifica "<<msg.toStdString ();
}

