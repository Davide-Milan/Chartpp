#include "view.h"

#include <QApplication>

#include "model.h"
#include "view.h"
#include "controller.h"
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Model m;
    View v;
    Controller c;

    c.setModel(&m);
    c.setView(&v);
    v.setController(&c);

    v.show();
    return a.exec();
}
