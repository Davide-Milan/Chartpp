#include "barChart.h"

BarChart::BarChart(QString _title, Matrix* dataSet, const QVector<int>& numericIndexes, int textIndex) : title(_title)
{
    if(textIndex >= 0){
        for(unsigned int y = 0; y < dataSet->getDataMatrixHeigth(); y++)
            textData.append(static_cast<TextData*>(dataSet->getDataAt(textIndex, y))->getData());
    }
    for(unsigned int col = 0; col < dataSet->getDataMatrixWidth(); col++){
        if(numericIndexes.contains(col)){
            QVector<double>* aux = new QVector<double>;
            for(unsigned int y = 0; y < dataSet->getDataMatrixHeigth(); y++)
                aux->append(static_cast<NumericData*>(dataSet->getDataAt(col,y))->getData());
            numericData.append(aux);
            columnsTitles.append(dataSet->getTitle(col));
        }
    }
}

BarChart::~BarChart()
{
    for(int x = 0; x < numericData.size(); x++)
        delete numericData.at(x);
}

QChart* BarChart::draw()
{
    QBarSeries* barSeries = new QBarSeries();
    for(int y = 0; y < numericData.at(0)->size(); y++){
        QBarSet* bar;
        if(!textData.isEmpty())
            bar = new QBarSet(textData.at(y));
        else
            bar = new QBarSet(QString::number(y+1));
        for(int x = 0; x < numericData.size(); x++)
            bar->append(numericData.at(x)->at(y));
        barSeries->append(bar);
    }
    QChart* chart = new QChart();
    chart->addSeries(barSeries);
    if(!columnsTitles.isEmpty()){
        QStringList categories;
        for(int i = 0; i < columnsTitles.size(); i++){
            categories.append(columnsTitles.at(i));
        }
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        barSeries->attachAxis(axisX);
        axisX->setRange(columnsTitles.at(0), columnsTitles.at(columnsTitles.size()-1));
        QValueAxis *axisY = new QValueAxis();
        chart->addAxis(axisY, Qt::AlignLeft);
        barSeries->attachAxis(axisY);
    }
    else chart->createDefaultAxes();
    chart->setTitle(title);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    return chart;
}
