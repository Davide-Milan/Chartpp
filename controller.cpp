#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

void Controller::setModel(Model *m) {model = m;}

void Controller::setView(View *v) { view = v;}

unsigned int Controller::getDataMatrixWidth() const {return model->getDataMatrixWidth();}

unsigned int Controller::getDataMatrixHeigth() const {return model->getDataMatrixHeigth();}

void Controller::addRow()
{
    model->addRowData();
    view->addRow();
}

void Controller::deleteRow()
{
    model->deleteRowData();
    view->deleteRow();
}

void Controller::addColumn()
{
    model->addColumnData();
    view->addColumn();
}

void Controller::deleteColumn()
{
    model->deleteColumnData();
    view->deleteColumn();
}
