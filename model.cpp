#include "model.h"

Model::Model() : matrix(new Matrix), chart(nullptr)
{
}

Model::~Model()
{
    delete chart;
    delete matrix;
}


/*GETTERS*/
unsigned int Model::getDataMatrixWidth() const
{
    if(matrix!=nullptr)
        return matrix->getDataMatrixWidth();
    return 0;
}
unsigned int Model::getDataMatrixHeigth() const
{
    if(matrix!=nullptr)
        return matrix->getDataMatrixHeigth();
    return 0;
}
QString Model::getColumnTitle(unsigned int col) const {return matrix->getTitle(col);}

Matrix* Model::getMatrix() const {return matrix;}

unsigned int Model::getNumberOfNumerics() const {return matrix->getNumberOfNumerics();}
unsigned int Model::getNumberOfTexts() const {return matrix->getNumberOfTexts();}

QVector<int>* Model::getNumericDataIndexes() const {return matrix->getNumericDataIndexes();}
QVector<int>* Model::getTextDataIndexes() const {return matrix->getTextDataIndexes();}

Chart* Model::getChart() const {return chart;}

void Model::deleteChart()
{
    if(chart != nullptr){
        delete chart;
        chart = nullptr;
    }
}

Chart* Model::createLineChart(QString title, const QVector<int>& numericIndexes)
{
    chart = new LineChart(title, matrix, numericIndexes);
    return chart;
}

Chart* Model::createBarChart(QString title, const QVector<int>& numericIndexes, int textIndex)
{
    chart = new BarChart(title, matrix, numericIndexes, textIndex);
    return chart;
}

Chart* Model::createPieChart(QString title, int numericIndex, int textIndex)
{
    chart = new PieChart(title, matrix, numericIndex, textIndex);
    return chart;
}


/*SETTERS*/
void Model::updateTitle(QString text, unsigned int col) const{matrix->updateTitle(text, col);}

void Model::updateDataMatrixValue(QString text, unsigned int x, unsigned int y) const{matrix->updateDataMatrixValue(text, x, y);}

/*MODIFIERS*/
void Model::addRowData() const{matrix->addRowMatrix();}

void Model::deleteRowData(unsigned int row) const{matrix->deleteRowMatrix(row);}

void Model::addColumnData(bool isNumeric) const{matrix->addColumnMatrix(isNumeric);}

void Model::deleteColumnData(unsigned int col) const{matrix->deleteColumnMatrix(col);}

bool Model::isNumeric(unsigned int col) const{return matrix->isNumeric(col);}


/*SUPPORT*/
void Model::loadData(const QJsonArray& json) const{matrix->loadData(json);}

void Model::clean(){
    delete matrix;
    deleteChart();
    matrix = new Matrix;
}


//write json and saves on file
void Model::writeFile(const QString& fileName) const
{
    QFile saveFile(fileName);
    if (!saveFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("Impossibile aprire il file.");
    QJsonArray jObj;

    for(unsigned int x = 0; x < matrix->getDataMatrixWidth(); x++){
        QJsonObject column;
        (dynamic_cast<NumericData*>(matrix->getDataAt(x,0))) ? column["type"] = "Numeric" : column["type"] = "Text";
        QJsonArray dataArray;
        NumericData* tmp = dynamic_cast<NumericData*>(matrix->getDataAt(x,0));
        if(tmp){
            for(unsigned int y = 0; y < matrix->getDataMatrixHeigth(); y++)
                dataArray.append(static_cast<NumericData*>(matrix->getDataAt(x,y))->getData());
        }
        else{
            TextData* tmp = dynamic_cast<TextData*>(matrix->getDataAt(x,0));
            if(tmp)
                for(unsigned int y = 0; y < matrix->getDataMatrixHeigth(); y++)
                    dataArray.append(static_cast<TextData*>(matrix->getDataAt(x,y))->getData());
        }
        column["title"] = getColumnTitle(x);
        column["data"] = dataArray;
        jObj.append(column);
    }

    saveFile.write(QJsonDocument(jObj).toJson());  //write on file
}
