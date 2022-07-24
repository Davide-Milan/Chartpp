#ifndef TEXTDATA_H
#define TEXTDATA_H

#include "data.h"

/**
 * direct Data subtype implementation for text data
 *
 * stores a string value that can be set dynamically with a generic Data pointer using setData and retrieved using downcasting from base class using "getData"
*/

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
