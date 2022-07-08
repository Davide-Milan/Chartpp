#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

void Controller::setModel(Model *m) {model = m;}

void Controller::setView(View *v) { view = v;}

unsigned int Controller::getDataMatrixWidth() const {return model->getDataMatrixWidth();}

unsigned int Controller::getDataMatrixHeigth() const {return model->getDataMatrixHeigth();}

void Controller::shiftRowsOnDelete(unsigned int x, unsigned int row)
{
    view->shiftRowsOnDelete(x, row);
    model->shiftRowsOnDelete(x, row);
}

void Controller::shiftColumnsOnDelete(unsigned int col)
{
    view->shiftColumnsOnDelete(col);
    model->shiftColumnsOnDelete(col);
}

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



void Controller::write(QJsonObject& jObj) const
{
    QVector<QVector<Data*>*> * data = model->getData();
    for(int x = 0; x < data->size(); x++){
        QJsonArray column;
        for(int y = 0; y < data->at(x)->size(); y++){
            QJsonObject value;
            value.insert("value/text", data->at(x)->at(y)->getData());
            column.append(value);
        }
        jObj[QString::number(x)] = column;
    }
}

bool Controller::saveToFile() const
{
    try {
        QString fileName = view->showSaveFile();
        QFile saveFile(fileName);
        if (!saveFile.open(QIODevice::WriteOnly)) {
            throw std::runtime_error("Impossibile aprire il file.");
        }
        QJsonObject sessionObject;
        write(sessionObject);
        saveFile.write(QJsonDocument(sessionObject).toJson());
        return true;
    }  catch (std::runtime_error& e) {
        e.what();
        return false;
    }
}
