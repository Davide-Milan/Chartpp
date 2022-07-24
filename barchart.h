#ifndef BARCHART_H
#define BARCHART_H

#include "chart.h"
#include "matrix.h"
#include "QBarSeries"


/**
 * direct Chart subtype implementation for Bar charts
 *
 * stores data from selected numeric columns (1 or more) and a text column (optional, max 1)
 * upon drawing using the "draw" method returns a QChart (from Qt library) to be drawn by the view
 * if a text column is selected every bar will be a representation of the text data in the same row in the data table, else each bar will have a number assigned, starting from 1
*/


class BarChart : public Chart
{
private:
    QString title;
    QVector<QString> columnsTitles;
    QVector<QVector<double>*> numericData;
    QVector<QString> textData;
public:
    BarChart(QString, Matrix*, const QVector<int>&, int);
    ~BarChart() override final;

    /**
     * @brief overrides Chart's virtual function draw: creates a QChart representing a Bar Chart and returns it;
     * every row of numeric data makes for a bar, drawn for every interval/category represented by one column of text data.
     * @returns pointer to QChart
    */
    QChart* draw() override;
};

#endif // BARCHART_H
