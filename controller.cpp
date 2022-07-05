#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

void Controller::setModel(Model *m) {model = m;}

void Controller::setView(View *v) { view = v;}
