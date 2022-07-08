#ifndef TEXTDATA_H
#define TEXTDATA_H

#include "data.h"

class TextData : public Data
{
private:
    QString value;
public:
    TextData(QString = "");
    ~TextData() override;
    void setData(QString) override;
    QString getData();
};

#endif // TEXTDATA_H
