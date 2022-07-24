#include "view.h"

#include <QApplication>

#include "model.h"
#include "view.h"
#include "controller.h"
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QString("Chart++"));
    Model m;
    View v;
    Controller c;

    c.setModel(&m);
    c.setView(&v);
    v.setController(&c);

    v.setFixedSize(1000, 600);
    v.show();
    return a.exec();
}
