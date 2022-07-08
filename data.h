#ifndef DATA_H
#define DATA_H

#include <QString>

//classe base astratta (pura(?))


class Data
{ 
public:
    Data();
    virtual ~Data() = 0;
    virtual void setData(QString) = 0;
};

#endif // DATA_H

//old declaration using polymorphism
//classe base astratta (pura(?))


//class Data
//{
//public:
//    Data();
//    virtual ~Data();
//    virtual void setData(QString) = 0;
//    virtual QString getData(){}
//    virtual double getData(bool = false){}    //fake bool argument that let's me use the same function signature for both derived classes
//};


