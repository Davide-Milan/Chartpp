#include "model.h"

Model::Model() : matrix(new Matrix)
{
}

void Model::addRowData()
{
    matrix->addRowMatrix();
}

void Model::deleteRowData()
{

}

void Model::addColumnData()
{
    matrix->addColumnMatrix();
}

void Model::deleteColumnData()
{

}

unsigned int Model::getDataMatrixWidth() const {
    if(matrix!=nullptr)
        //QTextStream(stdout) << "aaaaaaa" << endl; //LOG
        return matrix->getDataMatrixWidth();
    return 0;
}
unsigned int Model::getDataMatrixHeigth() const {
    if(matrix!=nullptr)
        //QTextStream(stdout) << "aaaaaaa" << endl; //LOG
        return matrix->getDataMatrixHeigth();
    return 0;
}
