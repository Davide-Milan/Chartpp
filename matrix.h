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
    QVector<QVector<Data*>*> dataMatrix;
public:
    Matrix();
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;
    void addRowMatrix();
    void addColumnMatrix();
};

#endif // MATRIX_H
