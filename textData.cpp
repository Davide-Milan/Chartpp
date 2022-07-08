#include "textData.h"

TextData::TextData(QString _value) : value(_value)
{

}


TextData::~TextData()
{
//qDebug() << "~TEXTDATA";
}

void TextData::setData(QString text){value = text;}

QString TextData::getData() {return value;}

