#include "model.h"

Model::Model() : matrix(new Matrix)
{
}

void Model::addRowData()
{
    matrix->addRowMatrix();
}

void Model::deleteRowData(unsigned int row)
{
    matrix->deleteRowMatrix(row);
}

void Model::addColumnData(bool numeric)
{
    matrix->addColumnMatrix(numeric);
}

void Model::deleteColumnData(unsigned int col)
{
    matrix->deleteColumnMatrix(col);
}

unsigned int Model::getDataMatrixWidth() const
{
    if(matrix!=nullptr)
        //qDebug() << "aaaaaaa" << endl; //LOG
        return matrix->getDataMatrixWidth();
    return 0;
}
unsigned int Model::getDataMatrixHeigth() const
{
    if(matrix!=nullptr)
        //qDebug() << "aaaaaaa" << endl; //LOG
        return matrix->getDataMatrixHeigth();
    return 0;
}

void Model::updateDataMatrixValue(QString text, unsigned int x, unsigned int y)
{
    matrix->updateDataMatrixValue(text, x, y);
}

void Model::shiftRowsOnDelete(unsigned int x, unsigned int row)
{

}

void Model::shiftColumnsOnDelete(unsigned int col)
{

}

Matrix* Model::getMatrix() const {return matrix;}

QVector<QVector<Data *>*>* Model::getData()
{
    return matrix->getMatrixMemory();
}

void Model::loadData(const QJsonArray& json)
{
   matrix->loadData(json);
}

void Model::clean(){
    delete matrix;
    matrix = new Matrix;
}
