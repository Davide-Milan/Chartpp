#include "model.h"

Model::Model() : data(nullptr)
{

}

void Model::addRowData()
{

}

void Model::deleteRowData()
{

}

void Model::addColumnData()
{

}

void Model::deleteColumnData()
{

}

unsigned int Model::getDataMatrixWidth() const {
    if(data!=nullptr)
        //QTextStream(stdout) << "aaaaaaa" << endl; //LOG
        return data->getDataMatrixWidth();
    return 0;
}
unsigned int Model::getDataMatrixHeigth() const {
    if(data!=nullptr)
        //QTextStream(stdout) << "aaaaaaa" << endl; //LOG
        return data->getDataMatrixHeigth();
    return 0;
}
