#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QJsonObject>
#include <QObject>

#include "view.h"
#include "model.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    View* view;
    Model* model;

    void write(QJsonObject &jObj) const;
public:
    explicit Controller(QObject *parent = nullptr);
    void setModel(Model*);
    void setView(View*);
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;
    void shiftRowsOnDelete(unsigned int, unsigned int);
    void shiftColumnsOnDelete(unsigned int);

public slots:
    void addRow();
    void deleteRow();
    void addColumn();
    void deleteColumn();

    void test(QPair<unsigned int, unsigned int> value){QTextStream(stdout) << QString::number(value.first) << QString::number(value.second) << endl;}
    void updateValue(QString, unsigned int, unsigned int);
    bool saveToFile() const;
};

#endif // CONTROLLER_H
