#ifndef TEXTDATA_H
#define TEXTDATA_H

#include <QString>
#include "data.h"

class TextData : public Data
{
private:
    QString value;
public:
    TextData();
};

#endif // TEXTDATA_H
