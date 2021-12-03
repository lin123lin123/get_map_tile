#include "rec_qmldata.h"
#include"mainwindow.h"
extern MainWindow *p;
rec_qmldata::rec_qmldata()
{
   // init_connect();
}

int rec_qmldata::getoperation()
{
    return operation;
}

void rec_qmldata::init_connect()
{

}

void rec_qmldata::setoperation(int adr)
{
    operation=adr;
}

void rec_qmldata::rec_operation_slot(int msg)
{
        operation=msg;
        if(operation==0x01)
        {
            qDebug()<<"rec_operation_slot";
            emit close_map();
        }
}
