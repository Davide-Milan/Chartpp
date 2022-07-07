#include "matrix.h"

Matrix::Matrix()
{
}

unsigned int Matrix::getDataMatrixWidth() const {

    return dataMatrix.size();
}


unsigned int Matrix::getDataMatrixHeigth() const {    
    return dataMatrix[0]->size();   
}

void Matrix::addRowMatrix(){
    for(int i = 0; i < dataMatrix.size(); i++){
        if(dynamic_cast<TextData*>(dataMatrix[i]->at(0)))
            dataMatrix[i]->append(new TextData);
        else
            dataMatrix[i]->append(new NumericData);
    }
}

void Matrix::addColumnMatrix(bool numeric)
{
    if(numeric){
        if(dataMatrix.isEmpty())
            dataMatrix.append(new QVector<Data*>(1, new NumericData)); //adds new QVector<Data*> with 1 default Data
        else{
            dataMatrix.append(new QVector<Data*>(dataMatrix[0]->size(), new NumericData)); //adds new QVector<Data*> with default Datas, as many as matrix heigth
        }
    }
    else{
        if(dataMatrix.isEmpty())
            dataMatrix.append(new QVector<Data*>(1, new TextData)); //adds new QVector<Data*> with 1 default Data
        else{
            dataMatrix.append(new QVector<Data*>(dataMatrix[0]->size(), new TextData)); //adds new QVector<Data*> with default Datas, as many as matrix heigth
        }
    }
}

void Matrix::deleteRowMatrix(unsigned int row)
{
    for(unsigned int x = 0; x < getDataMatrixWidth(); x++){
        Data* tmp = dataMatrix[x]->at(row);
        dataMatrix[x]->erase();
        delete tmp; //qua crasha
    }
}

void Matrix::deleteColumnMatrix(unsigned int col){
    QVector<Data*>* tmp = dataMatrix[col];
    dataMatrix.removeAt(col);
    delete tmp;
}

void Matrix::updateDataMatrixValue(QString text, unsigned int x, unsigned int y)
{
    dataMatrix[x]->at(y)->setData(text);
}
