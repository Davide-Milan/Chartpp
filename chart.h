#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <QChartView>
#include <QChart>

class Chart
{
public:
    Chart();
    virtual ~Chart()=0;
    virtual QChart* draw() = 0;
};

#endif // CHART_H
