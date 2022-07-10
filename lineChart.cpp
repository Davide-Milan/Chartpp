#include "lineChart.h"

LineChart::LineChart(QString _title, Matrix* dataSet, const QVector<int>& numericIndexes) : title(_title)
{
    int i = 0;
    for(unsigned int col = 0; col < dataSet->getDataMatrixWidth(); col++){
        if(numericIndexes.contains(col)){
            numericData.append(new QVector<double>);
            for(unsigned int y = 0; y < dataSet->getDataMatrixHeigth(); y++)
                numericData.at(i)->append(static_cast<NumericData*>(dataSet->getDataAt(col,y))->getData());
            i++;
            columnsTitles.append(dataSet->getTitle(col));
        }
    }
}

LineChart::~LineChart()
{

}

QChart* LineChart::draw()
{
    QChart* chart = new QChart();
    for(int i = 0; i < numericData.size(); i++){
        QLineSeries* line = new QLineSeries();
        line->setName(columnsTitles.at(i));
        for(int y = 0; y < numericData.at(0)->size(); y++)
            line->append(y, numericData.at(i)->at(y));
        chart->addSeries(line);
    }
    chart->createDefaultAxes();
    chart->setTitle(title);
    chart->legend()->setVisible(true);
    return chart;
}
