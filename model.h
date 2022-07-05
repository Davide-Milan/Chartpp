#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"
#include <QTextStream>
class Model
{
private:
    Matrix* data;
public:
    Model();

    void addRowData();
    void deleteRowData();
    void addColumnData();
    void deleteColumnData();
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;
};

#endif // MODEL_H
