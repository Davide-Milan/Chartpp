#include "matrix.h"

Matrix::Matrix()
{

}

Matrix::~Matrix()
{

    for(unsigned int x = 0; x < getDataMatrixWidth(); x++){
        for(unsigned int y=0; y < getDataMatrixHeigth(); y++){
            delete dataMatrix.at(x)->at(y);
        }
        delete dataMatrix.at(x);
        dataMatrix.at(x)->clear();
    }
    dataMatrix.clear();
    titles.clear();
}

unsigned int Matrix::getDataMatrixWidth() const {return dataMatrix.size();}

unsigned int Matrix::getDataMatrixHeigth() const
{
    if(dataMatrix.empty()) return 0;
    return dataMatrix.at(0)->size();
}

QString Matrix::getTitle(unsigned int col) const {return titles[col];}

void Matrix::updateTitle(QString text, unsigned int col){titles[col] = text;}

void Matrix::updateDataMatrixValue(QString text, unsigned int x, unsigned int y){dataMatrix.at(x)->at(y)->setData(text);}

Data* Matrix::getDataAt(unsigned int x, unsigned int y) const{return dataMatrix.at(x)->at(y);}

void Matrix::loadData(const QJsonArray& json)
{
    for(int x = 0; x < json.size(); x++){
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
        titles.append(json.at(x).toObject().value("title").toString());
    }
}

bool Matrix::isNumeric(unsigned int col) const
{
    if(dynamic_cast<NumericData*>(getDataAt(col))) return true;
    else return false;
}


void Matrix::printDebug() const
{
    for(unsigned int y = 0; y < getDataMatrixHeigth(); y++){
        for(unsigned int x = 0; x < getDataMatrixWidth(); x++){
            QString aux;
            if(dynamic_cast<NumericData*>(getDataAt(x))){
                aux = (QString::number(static_cast<NumericData*>(getDataAt(x,y))->getData()));
            }
            else{
                aux = static_cast<TextData*>(getDataAt(x,y))->getData();
            }
            QTextStream(stdout) << aux << "       ";
        }
        QTextStream(stdout) << "" << endl;
    }
    for(unsigned int x = 0; x < getDataMatrixWidth(); x++){
        QTextStream(stdout) << getTitle(x) + "       ";
    }
     QTextStream(stdout) << "" << endl;
}

void Matrix::addRowMatrix(){
    for(int x = 0; x < getDataMatrixWidth(); x++){
        if(isNumeric(x))
            dataMatrix.at(x)->append(new NumericData);
        else
            dataMatrix.at(x)->append(new TextData);
    }
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

void Matrix::addColumnMatrix(bool isNumeric)
{
    titles.push_back("");
    if(isNumeric){
        if(dataMatrix.isEmpty())
            dataMatrix.append(new QVector<Data*>(1, new NumericData)); //adds new QVector<Data*> with 1 default Data
        else{
            dataMatrix.append(new QVector<Data*>); //adds new QVector<Data*> with default NumericDatas, as many as matrix heigth
            for(unsigned int y = 0; y < getDataMatrixHeigth(); y++)
                dataMatrix.at(getDataMatrixWidth()-1)->push_back(new NumericData);
        }
    }
    else{
        if(dataMatrix.isEmpty())
            dataMatrix.append(new QVector<Data*>(1, new TextData)); //adds new QVector<Data*> with 1 default Data
        else{
            dataMatrix.append(new QVector<Data*>); //adds new QVector<Data*> with default TextDatas, as many as matrix heigth
            for(unsigned int y = 0; y < getDataMatrixHeigth(); y++)
                dataMatrix.at(getDataMatrixWidth()-1)->push_back(new TextData);
        }
    }
}

void Matrix::deleteColumnMatrix(unsigned int col){
    QVector<Data*>* tmp = dataMatrix.at(col);
    delete tmp;
    dataMatrix.erase(dataMatrix.begin() + col);
    titles.erase(titles.begin() + col);
}


unsigned int Matrix::getNumberOfNumerics() const
{
    unsigned int count = 0;
    for(unsigned int col = 0; col < getDataMatrixWidth(); col++){
        if(dynamic_cast<NumericData*>(getDataAt(col, 0)))
            count++;
    }
    return count;
}

unsigned int Matrix::getNumberOfTexts() const
{
    unsigned int count = 0;
    for(unsigned int col = 0; col < getDataMatrixWidth(); col++){
        if(dynamic_cast<TextData*>(getDataAt(col, 0)))
            count++;
    }
    return count;
}

QVector<int>* Matrix::getNumericDataIndexes() const
{
    QVector<int>* numericColumns = new QVector<int>;
    for(unsigned int col = 0; col < getDataMatrixWidth(); col++){
        if(isNumeric(col)){
            numericColumns->append(col);
        }
    }
    return numericColumns;
}


QVector<int>* Matrix::getTextDataIndexes() const
{
    QVector<int>* textColumns = new QVector<int>;
    for(unsigned int col = 0; col < getDataMatrixWidth(); col++){
        if(!isNumeric(col)){
            textColumns->append(col);
        }
    }
    return textColumns;
}

