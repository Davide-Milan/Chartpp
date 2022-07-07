#ifndef NUMERICDATA_H
#define NUMERICDATA_H

#include "data.h"

class NumericData : public Data
{
private:
    double value;
public:
    NumericData();
    ~NumericData() override;
    void setData(QString) override;
    double getData(bool = false) override;
};

#endif // NUMERICDATA_H
