#include "numericData.h"

NumericData::NumericData(double _value) : value(_value)
{
}

NumericData::~NumericData()
{
}

void NumericData::setData(QString text){value = text.toDouble();}

double NumericData::getData() {return value;}
