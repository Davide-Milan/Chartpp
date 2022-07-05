#include "matrix.h"

Matrix::Matrix()
{

}

unsigned int Matrix::getDataMatrixWidth() const {
    return dataMatrix.size();
}


unsigned int Matrix::getDataMatrixHeigth() const {
    return dataMatrix[0].size();
}
