#include "matrix.h"

Matrix::Matrix()
{
    //dataMatrix.push_back(new QVector<Data*>);
}

unsigned int Matrix::getDataMatrixWidth() const {

    return dataMatrix.size();
}


unsigned int Matrix::getDataMatrixHeigth() const {    
    return dataMatrix[0]->size();   
}

void Matrix::addRowMatrix(){

    if(dataMatrix.isEmpty())
        dataMatrix.append(new QVector<Data*>(1, new Data)); //adds new QVector<Data*> with 1 default Data
    else{
        for(int i = 0; i < dataMatrix.size(); i++){
            dataMatrix[i]->resize(dataMatrix[i]->size() + 1);   //adds one default item to every QVector inside of QVector (to every column of the matrix)
        }
    }

    QTextStream(stdout) << "Matrix heigth: " + QString::number(dataMatrix[0]->size())<<endl; //LOG
    QTextStream(stdout) << "Matrix width: " + QString::number(dataMatrix.size())<<endl;      //LOG
}

void Matrix::addColumnMatrix(){
    //dataMatrix.resize(dataMatrix.size() + 1);
    if(dataMatrix.isEmpty())
        dataMatrix.append(new QVector<Data*>(1, new Data)); //adds new QVector<Data*> with 1 default Data
    else{
        dataMatrix.append(new QVector<Data*>(dataMatrix[0]->size(), new Data)); //adds new QVector<Data*> with default Datas, as many as matrix heigth
    }

    QTextStream(stdout) << "Matrix heigth: " + QString::number(dataMatrix[0]->size())<<endl;    //LOG
    QTextStream(stdout) << "Matrix width: " + QString::number(dataMatrix.size())<<endl;         //LOG
}
