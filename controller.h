#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QJsonObject>
#include <QObject>

#include "view.h"
#include "model.h"


/**
 * handles communication between the View (interaction with user) and the Model (interaction with the data structures)
 * inherits from QObject in order to use Qt slot system
*/
class Controller : public QObject
{
    Q_OBJECT
private:
    View* view;
    Model* model;


    /**
     * @brief checks if any cell was selected in order to delete a row or column
     * @returns bool
    */
    bool anyCellSelected(bool);
    bool dataIsEmpty();

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void setModel(Model*);
    void setView(View*);
    unsigned int getDataMatrixWidth() const;    //calls Model's getDataMatrixWidth
    unsigned int getDataMatrixHeigth() const;   //calls Model's getDataMatrixHeigth

    /**
     * @brief creates a pointer to the model's Matrix object and returns it
     * Should be called by the View
     * @returns pointer to Matrix
    */
    Matrix* getDataMatrix() const;
    bool isNumeric(unsigned int col) const;     //calls Model's isNumeric    
public slots:

    /**
     * @brief adds a row of TextBoxes to the View and a "row" of pointers to Data in the model's Matrix
     * Called by the "Add row" button
    */
    void addRow();

    /**
     * @brief deletes the row of TextBoxes of the last selected TextBox from the View and a "row" from the model's Matrix
     * If no cell has been selected previously, the View will show a pop-up message and nothing will happen
     * Called by the "Delete row" button
    */
    void deleteRow();

    /**
     * @brief adds a column of TextBoxes of the selected type (numeric or text) to the View and a "column" of pointers to Data in the model's Matrix
     * Called by the "Add column" button
    */
    void addColumn();

    /**
     * @brief deletes the column of TextBoxes of the last selected TextBox from the View and a "column" from the model's Matrix
     * If no cell has been selected previously, the View will show a pop-up message and nothing will happen
     * Called by the "Delete column" button
    */
    void deleteColumn();

    // creation process for different types of charts, based on the button clicked
    void lineChart();
    void barChart();
    void pieChart();

    /**
     * @brief View opens a file dialog and saves Model's Matrix to the file in JSON format
     * Called by the "Export" button and File menu button
    */
    bool saveToFile() const;

    /**
     * @brief View opens a file dialog and passes the JSON to the Model to create the Matrix by parsing the file
     * Called by the "Open File" button and File menu button
    */
    void loadDataFromFile();

    /**
     * @brief deletes Matrix and cleans View
     * Called by the "Clear all" Edit menu button
    */
    void clearData();

    /**
     * @brief works just like clear data - for future development of the software
     * Called by the "New File" File menu button
    */
    void newFile();

    /**
     * @brief updates the value in the Matrix at the selected location based on the text of the corresponding TextBox emitting the signal
     *
     * @param QString value
     * @param unsigned int (x) column to save into
     * @param unsigned int (y) row to save into
    */
    void updateValue(QString, unsigned int, unsigned int);

    /**
     * @brief updates value in the Matrix's titles QVector based on the text of the corresponding TextBox emitting the signal
    */
    void updateTitle(QString, unsigned int);

    /**
     * @brief deletes the viewed Chart after the View hides it
    */
    void deleteChart();

    /**
     * @brief opens the project repository link on GitHub on the system's default browser where you can find everything you need to use the software
    */
    bool openRepositoryLink();
};

#endif // CONTROLLER_H

