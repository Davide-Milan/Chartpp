#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"
#include <QTextStream>
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

    void updateDataMatrixValue(QString, unsigned int, unsigned int);
};

#endif // MODEL_H
