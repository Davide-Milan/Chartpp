#include "pieChart.h"

PieChart::PieChart(QString _title, Matrix* dataSet, int numericIndex, int textIndex) : title(_title)
{
    if(textIndex >= 0){
        for(unsigned int y = 0; y < dataSet->getDataMatrixHeigth(); y++)
            textData.append(static_cast<TextData*>(dataSet->getDataAt(textIndex, y))->getData());
    }

    for(unsigned int y = 0; y < dataSet->getDataMatrixHeigth(); y++)
        numericData.append(static_cast<NumericData*>(dataSet->getDataAt(numericIndex,y))->getData());
    dataTitle = dataSet->getTitle(numericIndex);
}

PieChart::~PieChart()
{

}

QChart* PieChart::draw()  //piechart that associate entities of a set each to a value and pops the biggest one
{
    QPieSeries* series = new QPieSeries();
    int biggestValue = 0;
    int biggestIndex = 0;
    for(int y = 0; y < numericData.size(); y++){
        series->append(textData.at(y), numericData.at(y));
        if(y==0) biggestValue = numericData.at(0);
        else if(biggestValue < numericData.at(y)){
            biggestValue = numericData.at(y);
            biggestIndex = y;
        }
    }
    QPieSlice *slice = series->slices().at(biggestIndex);
    slice->setExploded();
    slice->setLabelVisible();
    slice->setPen(QPen(Qt::darkgreen, 2));
    slice->setBrush(Qt::red);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    return chart;
}
