#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QTextStream>

//classe base astratta (pura(?))

template<class T>
class Data
{
private:
    T value;
public:
    Data();
//    ~Data();
    void setData(T);
    T getData();
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


