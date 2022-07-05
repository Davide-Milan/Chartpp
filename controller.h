#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "view.h"
#include "model.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    View* view;
    Model* model;

    void setModel(Model*);
    void setView(View*);
public:
    explicit Controller(QObject *parent = nullptr);

signals:

};

#endif // CONTROLLER_H
