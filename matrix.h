#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include "data.h"
#include "numericData.h"
#include "textData.h"
#include <QJsonObject>
#include <QJsonArray>


class Matrix
{
private:
    QVector<QString> titles;
    QVector<QVector<Data *> *> dataMatrix;
public:
    Matrix();
    ~Matrix();
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;
    void addRowMatrix();
    void deleteRowMatrix(unsigned int);
    void addColumnMatrix(bool);
    void deleteColumnMatrix(unsigned int);
    void updateDataMatrixValue(QString, unsigned int, unsigned int);
    QVector<QVector<Data *> *>* getMatrixMemory();
    Data* getDataAt(unsigned int=0, unsigned int=0) const;    //by default gives the first Data* of the first vector
    void loadData(const QJsonArray&);
    void print() const;

    QString getTitle(unsigned int =0);
    void updateTitle(QString, unsigned int);
};

#endif // MATRIX_H
