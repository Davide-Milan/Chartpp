#include "data.h"

template<class T>
Data<T>::Data()
{

}
template<class T>
Data<T>::~Data()
{
    //QTextStream(stdout) << "~DATA";
}

template<class T>
void Data<T>::setData(T _value) {value = _value;}

template<class T>
T Data<T>::getData() {return value;}
