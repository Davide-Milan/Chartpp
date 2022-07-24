#ifndef LINECHART_H
#define LINECHART_H

#include "chart.h"
#include "matrix.h"
#include <QLineSeries>


/**
 * direct Chart subtype implementation for Line charts
 *
 * stores data from selected numeric columns (1 or more)
 * upon drawing using the "draw" method returns a QChart (from Qt library) to be drawn by the view
 * every numeric column selected will be represented by a line on the chart
*/

class LineChart : public Chart
{
private:
    QString title;
    QVector<QVector<double>*> numericData;
    QVector<QString> columnsTitles;
public:
    LineChart(QString, Matrix*, const QVector<int>&);
    ~LineChart() override final;

    /**
     * @brief overrides Chart's virtual function draw: creates a QChart representing a Bar Chart and returns it;
     * draws a line for each column of data selected.
     * @returns pointer to QChart
    */
    QChart* draw() override;
};

#endif // LINECHART_H
