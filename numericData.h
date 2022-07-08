#ifndef NUMERICDATA_H
#define NUMERICDATA_H

#include "data.h"

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
