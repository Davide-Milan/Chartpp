#include "textData.h"

TextData::TextData(QString _value) : value(_value)
{
}


TextData::~TextData()
{
}

void TextData::setData(QString text){value = text;}

QString TextData::getData() {return value;}

