#include "textData.h"

TextData::TextData() : value("aaaaa")
{

}


TextData::~TextData()
{
//QTextStream(stdout) << "~TEXTDATA";
}

void TextData::setData(QString text){value = text;}

QString TextData::getData() {return value;}

