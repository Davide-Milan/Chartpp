#ifndef NUMERICDATA_H
#define NUMERICDATA_H

#include "data.h"

/**
 * direct Data subtype implementation for numeric data
 *
 * stores a double value that can be set dynamically with a generic Data pointer using setData and retrieved using downcasting from base class using "getData"
*/


class NumericData : public Data
{
private:
    double value;
public:
    NumericData(double = 0.0);
    ~NumericData() override;
    void setData(QString) override;
    double getData();
};


#endif // NUMERICDATA_H
