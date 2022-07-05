#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include "data.h"
#include "numericData.h"
#include "textData.h"

class Matrix
{
private:
    QVector<QVector<Data*>> dataMatrix;
public:
    Matrix();
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;
};

#endif // MATRIX_H
