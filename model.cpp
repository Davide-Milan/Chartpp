#include "model.h"

Model::Model() : matrix(new Matrix), chart(nullptr)
{
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
const QVector<QVector<Data *>*>* Model::getData() const {return matrix->getMatrixMemory();}
Matrix* Model::getMatrix() const {return matrix;}

unsigned int Model::getNumberOfNumerics() const {return matrix->getNumberOfNumerics();}
unsigned int Model::getNumberOfTexts() const {return matrix->getNumberOfTexts();}

QVector<int>* Model::getNumericDataIndexes() const {return matrix->getNumericDataIndexes();}
QVector<int>* Model::getTextDataIndexes() const {return matrix->getTextDataIndexes();}

Chart* Model::getChart() const {return chart;}

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
void Model::updateTitle(QString text, unsigned int col){matrix->updateTitle(text, col);}

void Model::updateDataMatrixValue(QString text, unsigned int x, unsigned int y){matrix->updateDataMatrixValue(text, x, y);}

/*MODIFIERS*/
void Model::addRowData(){matrix->addRowMatrix();}

void Model::deleteRowData(unsigned int row){matrix->deleteRowMatrix(row);}

void Model::addColumnData(bool isNumeric){matrix->addColumnMatrix(isNumeric);}

void Model::deleteColumnData(unsigned int col){matrix->deleteColumnMatrix(col);}

bool Model::isNumeric(unsigned int col) const{return matrix->isNumeric(col);}


/*SUPPORT*/
void Model::loadData(const QJsonArray& json){matrix->loadData(json);}

void Model::clean(){
    delete matrix;
    matrix = new Matrix;
}
