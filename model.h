#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"
#include "chart.h"
#include "lineChart.h"
#include "barChart.h"
#include "pieChart.h"

class Model
{
private:
    Matrix* matrix;
    Chart* chart;
public:
    Model();

    void addRowData();
    void deleteRowData(unsigned int);
    void addColumnData(bool);
    void deleteColumnData(unsigned int);
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;

    void updateTitle(QString text, unsigned int x);
    void updateDataMatrixValue(QString, unsigned int, unsigned int);
    const QVector<QVector<Data *> *>* getData() const;
    Matrix* getMatrix() const;
    void loadData(const QJsonArray&);

    void clean();
    QString getColumnTitle(unsigned int) const;
    bool isNumeric(unsigned int=0) const;
    unsigned int getNumberOfNumerics() const;
    unsigned int getNumberOfTexts() const;
    QVector<int>* getNumericDataIndexes() const;
    QVector<int>* getTextDataIndexes() const;
    Chart* getChart() const;

    Chart* createLineChart(QString title, const QVector<int>&);
    Chart* createBarChart(QString title, const QVector<int>&, int);
    Chart *createPieChart(QString title, int numericIndex, int textIndex);
};

#endif // MODEL_H
