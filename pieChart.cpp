#include "pieChart.h"

PieChart::PieChart(QString _title, Matrix* dataSet, int numericIndex, int textIndex) : title(_title)
{
    if(textIndex >= 0){
        for(unsigned int y = 0; y < dataSet->getDataMatrixHeigth(); y++)
            textData.append(static_cast<TextData*>(dataSet->getDataAt(textIndex, y))->getData());
    }

    if(numericIndex >= 0){
        for(unsigned int y = 0; y < dataSet->getDataMatrixHeigth(); y++)
            numericData.append(static_cast<NumericData*>(dataSet->getDataAt(numericIndex,y))->getData());
    }
    if(numericIndex >= 0)
        dataTitle = dataSet->getTitle(numericIndex);
    else
        dataTitle = dataSet->getTitle(textIndex);
}

PieChart::~PieChart()
{

}

QChart* PieChart::draw()
{
    QPieSeries* series = new QPieSeries();    
    int popOutIndex = 0;
    if(numericData.size() > 0){ //one numeric column selected
        int biggestValue = 0;
        for(int y = 0; y < numericData.size(); y++){  //populates the chart: every slice shows the value of the given numeric data
            if(textData.size()>0)   //also a text column selected
                series->append(textData.at(y), numericData.at(y)); //the text data in the same row in the view becomes its label
            else    //no text column selected
                series->append(QString::number(numericData.at(y)), numericData.at(y));  //the slices' labels are named incrementally from 1
            if(y==0) biggestValue = numericData.at(0);
            else if(biggestValue < numericData.at(y)){
                biggestValue = numericData.at(y);
                popOutIndex = y;
            }
        }
    }
    else{   //only a text column selected and no numeric column
        int mostRepeatedData = 0;
        QMap<QString, int> dataRepetition;
        for(int y = 0; y < textData.size(); y++){   //maps how many times each distinct text data appears
            if(!dataRepetition.contains(textData.at(y)))
                dataRepetition.insert(textData.at(y), 1);
            else
                dataRepetition[textData.at(y)] = dataRepetition.value(textData.at(y)) + 1;
        }

        for(int y = 0; y < dataRepetition.size(); y++){ //populates the chart with the mapped data: every slice shows how many times each distinct text data appears
                series->append(dataRepetition.keys()[y], dataRepetition.value(dataRepetition.keys()[y]));
            if(y==0) mostRepeatedData = dataRepetition.value(dataRepetition.keys()[y]);
            else if(mostRepeatedData < dataRepetition.value(dataRepetition.keys()[y])){
                mostRepeatedData = dataRepetition.value(dataRepetition.keys()[y]);
                popOutIndex = y;
            }
        }
    }
    QPieSlice *slice = series->slices().at(popOutIndex);
    slice->setExploded();
    slice->setLabelVisible();
    slice->setPen(QPen(Qt::black, 2));
    slice->setBrush(Qt::red);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    return chart;
}
