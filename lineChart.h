#ifndef LINECHART_H
#define LINECHART_H

#include "chart.h"
#include "matrix.h"
#include <QLineSeries>

class LineChart : public Chart
{

private:
    QString title;
    QVector<QVector<double>*> numericData;
    QVector<QString> columnsTitles;
public:
    LineChart(QString, Matrix*, const QVector<int>&);
    ~LineChart() override final;

    QChart* draw() override;
};

#endif // LINECHART_H
