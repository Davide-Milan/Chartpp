#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <QChartView>
#include <QChart>


/**
 * pure abstract base class (ABC) for charts representations allowing for polymorphic pointer behavior
*/

class Chart
{
public:
    Chart();
    virtual ~Chart() = 0;
    virtual QChart* draw() = 0;
};

#endif // CHART_H
