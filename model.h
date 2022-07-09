#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"

class Model
{
private:
    Matrix* matrix;
public:
    Model();

    void addRowData();
    void deleteRowData(unsigned int);
    void addColumnData(bool);
    void deleteColumnData(unsigned int);
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;

    void updateTitle(QString text, unsigned int x);
    void updateDataMatrixValue(QString, unsigned int, unsigned int);
    QVector<QVector<Data *> *>* getData();
    Matrix* getMatrix() const;
    void loadData(const QJsonArray&);

    void clean();
};

#endif // MODEL_H
