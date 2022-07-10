#ifndef BARCHART_H
#define BARCHART_H

#include "chart.h"
#include "matrix.h"
#include "QBarSeries"

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

    QChart* draw() override;
};

#endif // BARCHART_H
