#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

void Controller::setModel(Model *m) {model = m;}

void Controller::setView(View *v) { view = v;}

unsigned int Controller::getDataMatrixWidth() const {return model->getDataMatrixWidth();}

unsigned int Controller::getDataMatrixHeigth() const {return model->getDataMatrixHeigth();}

void Controller::addRow()
{    
    int size = model->getDataMatrixWidth();
    if(size == 0){
        bool numeric;
        QString selection = view->showSelectNewColumnType();
        if (selection.isEmpty())
            return;
        if(selection == "Numeric") numeric = true;
        else numeric = false;
        model->addColumnData(numeric);
        //this way it handles the Numeric or Text choice without adding a new function
    }
    else
        model->addRowData();
    view->addRow();
}

void Controller::deleteRow()
{
    if(!TextBox::somethingWasSelected){
        QMessageBox msgBox;
        msgBox.setText("No row selected");
        msgBox.exec();
        return;
    }
    TextBox::somethingWasSelected = false;
    unsigned int size = getDataMatrixHeigth();
    if (size > 0){
        unsigned int row = TextBox::getLastSelectedTextBoxCoordinates().second;
        view->deleteRow(row);
        model->deleteRowData(row);
    }
    QTextStream(stdout) << "Matrix width: " + QString::number(getDataMatrixWidth()) << endl;
    QTextStream(stdout) << "Matrix heigth: " + QString::number(getDataMatrixHeigth()) << endl;
}

void Controller::addColumn()
{
    bool numeric;
    QString selection = view->showSelectNewColumnType();
    if (selection.isEmpty())
        return;
    if(selection == "Numeric") numeric = true;
    else numeric = false;
    model->addColumnData(numeric);
    view->addColumn();
}

void Controller::deleteColumn()
{
    if(!TextBox::somethingWasSelected){
        QMessageBox msgBox;
        msgBox.setText("No column selected");
        msgBox.exec();
        return;
    }

    TextBox::somethingWasSelected = false;
    unsigned int size = getDataMatrixWidth();
    if (size > 0){
        unsigned int col = TextBox::getLastSelectedTextBoxCoordinates().first;
        view->deleteColumn(col);
        model->deleteColumnData(col);
    }
}

void Controller::updateValue(QString text, unsigned int x, unsigned int y){model->updateDataMatrixValue(text, x, y);}
