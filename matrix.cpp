#include "matrix.h"

Matrix::Matrix()
{

}

Matrix::~Matrix()
{
    //print(); //LOG
    for(unsigned int x = 0; x < getDataMatrixWidth(); x++){
        for(unsigned int y=0; y < getDataMatrixHeigth(); y++){
            delete dataMatrix.at(x)->at(y);
            //qDebug() << QString::number(x*y);
        }
        delete dataMatrix.at(x);
        dataMatrix.at(x)->clear();
    }
    dataMatrix.clear();
}

unsigned int Matrix::getDataMatrixWidth() const {
    if(dataMatrix.empty()) return 0;
    return dataMatrix.size();
}


unsigned int Matrix::getDataMatrixHeigth() const {    
    if(dataMatrix.empty()) return 0;
    if(dataMatrix.at(0)->empty()) return 0;
    return dataMatrix.at(0)->size();
}

void Matrix::print() const
{
    for(unsigned int y = 0; y < getDataMatrixHeigth(); y++){
        for(unsigned int x = 0; x < getDataMatrixWidth(); x++){
            if(dynamic_cast<NumericData*>(getDataAt(x))){
                QString tmp = (QString::number(static_cast<NumericData*>(getDataAt(x,y))->getData()));
                QTextStream(stdout) << tmp << " ";
            }
            else{
                QString tmp = static_cast<TextData*>(getDataAt(x,y))->getData();
                QTextStream(stdout) << tmp << " ";
            }
        }
        QTextStream(stdout) << " " << endl;
    }
}

QString Matrix::getTitle(unsigned int x){return titles[x];}


void Matrix::addRowMatrix(){
    for(int x = 0; x < getDataMatrixWidth(); x++){
        if(dynamic_cast<TextData*>(dataMatrix.at(x)->at(0)))
            dataMatrix.at(x)->append(new TextData);
        else
            dataMatrix.at(x)->append(new NumericData);
    }
}

void Matrix::addColumnMatrix(bool numeric)
{
    //titles.push_back("");
    if(numeric){
        if(dataMatrix.isEmpty())
            dataMatrix.append(new QVector<Data*>(1, new NumericData)); //adds new QVector<Data*> with 1 default Data
        else{
            dataMatrix.append(new QVector<Data*>(dataMatrix.at(0)->size(), new NumericData)); //adds new QVector<Data*> with default NumericDatas, as many as matrix heigth
        }
    }
    else{
        if(dataMatrix.isEmpty())
            dataMatrix.append(new QVector<Data*>(1, new TextData)); //adds new QVector<Data*> with 1 default Data
        else{
            dataMatrix.append(new QVector<Data*>(dataMatrix.at(0)->size(), new TextData)); //adds new QVector<Data*> with default TextDatas, as many as matrix heigth
        }
    }
    print();
}


void Matrix::deleteRowMatrix(unsigned int row)
{
    for(unsigned int x = 0; x < getDataMatrixWidth(); x++){
        Data* tmp = dataMatrix.at(x)->at(row);
        delete tmp; //qua crasha??
        dataMatrix.at(x)->erase(dataMatrix.at(x)->begin() + row);
    }
    if(dataMatrix.at(0)->isEmpty()){
        for(int x = getDataMatrixWidth()-1; x >= 0; x--){
            deleteColumnMatrix(x);
        }
    }
}

void Matrix::deleteColumnMatrix(unsigned int col){
    QVector<Data*>* tmp = dataMatrix.at(col);
    delete tmp;
    dataMatrix.erase(dataMatrix.begin() + col);
    //titles.erase(titles.begin() + col);
}

void Matrix::updateTitle(QString text, unsigned int x){titles[x] = text;}


void Matrix::updateDataMatrixValue(QString text, unsigned int x, unsigned int y)
{
    QTextStream(stdout) << x << " " << y << endl;
    QTextStream(stdout) << static_cast<NumericData*>(dataMatrix.at(x)->at(y+1))->getData()  << endl;
    dataMatrix.at(x)->at(y)->setData(text);
    QTextStream(stdout) << static_cast<NumericData*>(dataMatrix.at(x)->at(y+1))->getData() << endl;
    print();
}



QVector<QVector<Data *>*>* Matrix::getMatrixMemory()
{
    return &dataMatrix;
}

Data* Matrix::getDataAt(unsigned int x, unsigned int y) const
{
    return dataMatrix.at(x)->at(y);
}

void Matrix::loadData(const QJsonArray& json)
{
    for(int x = 0; x < json.size(); x++){
        //qDebug() << json.at(x).toObject().value("type").toString();
        dataMatrix.append(new QVector<Data*>);
        QJsonArray data = json.at(x).toObject().value("data").toArray();
        if(json.at(x).toObject().value("type").toString() == "Numeric"){
            for(int y = 0; y < data.size(); y++)
                dataMatrix.at(x)->append(new NumericData(data.at(y).toDouble()));
        }
        else{
            for(int y = 0; y < data.size(); y++)
                dataMatrix.at(x)->append(new TextData(data.at(y).toString()));
        }

    }
}
