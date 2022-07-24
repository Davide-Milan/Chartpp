#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"
#include "chart.h"
#include "lineChart.h"
#include "barChart.h"
#include "pieChart.h"

/**
 * it's a collection of pointers to the data types used by the software, a pointer to Matrix and a pointer to Chart
 * most of the methos of this class are getters or setters that call the pointers actual methods
 * this way we don't need to change the logic of the Model, but only the way the actual pointed objects do their job
 * most methods are declared const because they don't directly change the Model class, but only the objects pointed by its pointers which will handle their own const-correctness
*/


class Model
{
private:
    Matrix* matrix;
    Chart* chart;
public:
    Model();
    ~Model();

    void addRowData() const;
    void deleteRowData(unsigned int) const;
    void addColumnData(bool) const;
    void deleteColumnData(unsigned int) const;
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;

    void updateTitle(QString text, unsigned int x) const;
    void updateDataMatrixValue(QString, unsigned int, unsigned int) const;
    Matrix* getMatrix() const;
    void loadData(const QJsonArray&) const;

    void clean();
    QString getColumnTitle(unsigned int) const;
    bool isNumeric(unsigned int=0) const;
    unsigned int getNumberOfNumerics() const;
    unsigned int getNumberOfTexts() const;
    QVector<int>* getNumericDataIndexes() const;
    QVector<int>* getTextDataIndexes() const;
    Chart* getChart() const;

    /**
    *   @brief deletes and sets chart to nullptr
    *   Used when cleaning the whole data grid and when closing a chart view.
    */
    void deleteChart();

    Chart* createLineChart(QString title, const QVector<int>&);
    Chart* createBarChart(QString title, const QVector<int>&, int);
    Chart *createPieChart(QString title, int numericIndex, int textIndex);

    /**
     * @brief iterates through the Matrix data and saves it as a JSON array on a JSON file
    */
    void writeFile(const QString &) const;
};

#endif // MODEL_H
