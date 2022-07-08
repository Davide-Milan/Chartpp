#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include "data.h"
#include "numericData.h"
#include "textData.h"
#include <QTextStream>


class Matrix
{
private:
    QVector<QVector<Data *> *> dataMatrix;
public:
    Matrix();
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;
    void addRowMatrix();
    void deleteRowMatrix(unsigned int);
    void addColumnMatrix(bool);
    void deleteColumnMatrix(unsigned int);
    void updateDataMatrixValue(QString, unsigned int, unsigned int);
    QVector<QVector<Data *> *>* getData();
};

#endif // MATRIX_H
