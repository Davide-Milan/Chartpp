#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"

class Model
{
private:
    Matrix* matrix;
public:
    Model();

    void addRowData();
    void deleteRowData(unsigned int);
    void addColumnData(bool);
    void deleteColumnData(unsigned int);
    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;

    void updateTitle(QString text, unsigned int x);
    void updateDataMatrixValue(QString, unsigned int, unsigned int);
    const QVector<QVector<Data *> *>* getData() const;
    Matrix* getMatrix() const;
    void loadData(const QJsonArray&);

    void clean();
    QString getColumnTitle(unsigned int) const;
    bool isNumeric(unsigned int=0) const;
};

#endif // MODEL_H
