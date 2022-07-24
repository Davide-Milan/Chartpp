#ifndef PIECHART_H
#define PIECHART_H

#include "chart.h"
#include "matrix.h"
#include "barChart.h"


/**
 * direct Chart subtype implementation for Pie charts
 *
 * stores data from a selected numeric column (1) and a text column (optional, max 1)
 * upon drawing using the "draw" method returns a QChart (from Qt library) to be drawn by the view
 * every cell of the selected numeric column will represent a "slice" of the pie chart
*/

class PieChart : public Chart
{
private:
    QString title;
    QVector<double> numericData;
    QVector<QString> textData;
    QString dataTitle;
public:
    PieChart(QString, Matrix*, int, int);
    ~PieChart() override final;

    /**
     * @brief overrides Chart's virtual function draw: creates a QChart representing a Bar Chart and returns it;
     * If there's at least one selected numeric column: every data from a numeric data column is associated with data from another text data column (or with an incrementing number starting from 1 if no text column is selected) and the data with the biggest value is visually popped out of the pie.
     * If only a text column is selected : it gets counted how many time each distinc text data appears in the column and the data that is repeated the most times is visually popped out of the pie.
     * @returns pointer to QChart
    */
    QChart* draw() override;
};

#endif // PIECHART_H
