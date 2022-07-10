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

    void write(QJsonArray&) const;
    void read(const QJsonArray&);
    bool anyCellSelected(bool);

public:
    explicit Controller(QObject *parent = nullptr);
    void setModel(Model*);
    void setView(View*);
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;
    Matrix* getDataMatrix() const;    
    bool isNumeric(unsigned int col) const;

public slots:
    void addRow();
    void deleteRow();
    void addColumn();
    void deleteColumn();

    void lineData();
    void barData();
    void pieData();

    bool saveToFile() const;
    void loadDataFromFile();
    void clearData();
    void newFile();

    void updateValue(QString, unsigned int, unsigned int);
    void updateTitle(QString, unsigned int);
    void deleteChart();
};

#endif // CONTROLLER_H

