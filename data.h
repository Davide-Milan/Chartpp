#ifndef DATA_H
#define DATA_H

#include <QString>

/**
 * pure abstract base class (ABC) for data representations allowing for RTTI behavior using down casts to either numeric or text subtypes
*/

class Data
{ 
public:
    Data();
    virtual ~Data() = 0;
    virtual void setData(QString) = 0;
};

#endif
