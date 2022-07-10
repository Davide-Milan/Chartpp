#ifndef PIECHART_H
#define PIECHART_H

#include "chart.h"
#include "matrix.h"
#include "barChart.h"

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

    QChart* draw() override;
};

#endif // PIECHART_H
