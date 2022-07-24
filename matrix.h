#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include "data.h"
#include "numericData.h"
#include "textData.h"
#include <QJsonObject>
#include <QJsonArray>


/**
 * Implementation of a way to collect all the data written in the table cells in the view
 *
 * stores columns titles into a QVector of QStrings
 * stores columns data into a QVector of pointers to QVectors of pointers to the generic type Data
 *
 * It is not really a single matrix in itself, but the visual idea behind it is a matrix, a simple way of representing data in the same way as it is displayed in the view
*/

class Matrix
{
private:
    QVector<QString> titles;
    QVector<QVector<Data *> *> dataMatrix;  //matrix storing generic pointers to Data: this way it can point to either Text or Numeric Data using polymorphism
public:
    Matrix();
    ~Matrix();

    // methods that handle and work on the dataMatrix QVector

    unsigned int getDataMatrixWidth() const;
    unsigned int getDataMatrixHeigth() const;
    void addRowMatrix();
    void deleteRowMatrix(unsigned int);
    void addColumnMatrix(bool);
    void deleteColumnMatrix(unsigned int);


    /**
     * @brief sets new data value to an object pointed by the pointer at a certain position inside the matrix
     *
     * @param QString Value to be assigned
     * @param unsigned int Column (x) to gather the pointer from
     * @param unsigned int Row (y) to gather the pointer from
    */
    void updateDataMatrixValue(QString, unsigned int, unsigned int);


    /**
     * @brief returns the pointer to a generic Data, from the matrix at the indicated position, to be later downcasted to either TextData or NumericData
     *
     * @param unsigned int Column (x) to gather the pointer from, default 0
     * @param unsigned int Row (y) to gather the pointer from, default 0
    */
    Data* getDataAt(unsigned int=0, unsigned int=0) const;


    /**
     * @brief load the matrix with data gathered from a JSON file

     * @param const QJsonAray& json array to be parsed
    */
    void loadData(const QJsonArray&);


    /**
     * @brief checks if the selected column contains numeric data

     * @param bool
    */
    bool isNumeric(unsigned int) const;


    /**
     * @brief counts how many columns in the matrix represent numeric data
     *
     * @returns unsigned int
    */
    unsigned int getNumberOfNumerics() const;


    /**
     * @brief counts how many columns in the matrix represent text data
     *
     * @returns unsigned int
    */
    unsigned int getNumberOfTexts() const;


    /**
     * @brief creates, in the heap, a QVector of integers containing all the indexes at which the columns in the matrix represent numeric data
     *
     * @returns pointer to QVector<int>
    */
    QVector<int>* getNumericDataIndexes() const;


    /**
     * @brief creates, in the heap, a QVector of integers containing all the indexes at which the columns in the matrix represent text data
     *
     * @returns pointer to QVector<int>
    */
    QVector<int>* getTextDataIndexes() const;



    // methods that handle and work on the titles QVector

    QString getTitle(unsigned int =0) const;
    void updateTitle(QString, unsigned int);



    /**
     * @brief debug method that prints the whole matrix in the console - removed in production code
    */
    void printDebug() const;
};

#endif // MATRIX_H
