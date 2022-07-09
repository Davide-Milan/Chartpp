#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

void Controller::setModel(Model *m) {model = m;}

void Controller::setView(View *v) { view = v;}

unsigned int Controller::getDataMatrixWidth() const {return model->getDataMatrixWidth();}

unsigned int Controller::getDataMatrixHeigth() const {return model->getDataMatrixHeigth();}


Matrix *Controller::getDataMatrix() const {return model->getMatrix();}

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
//        view->deleteRow(row);
//        model->deleteRowData(row); //old
        view->clean();
        model->deleteRowData(row);
        view->loadData(getDataMatrix());
    }
}

void Controller::addColumn()
{
    TextBox::somethingWasSelected = false;
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
//        view->deleteColumn(col);
//        model->deleteColumnData(col); //old
        view->clean();
        model->deleteColumnData(col);
        view->loadData(getDataMatrix());
    }
}

void Controller::updateValue(QString text, unsigned int x, unsigned int y){
    model->updateDataMatrixValue(text, x, y);
    //qDebug() << x << " " << y;
}

void Controller::updateTitle(QString text, unsigned int x)
{
    model->updateTitle(text, x);
}



void Controller::write(QJsonArray& jObj) const
{
    QVector<QVector<Data*>*> * data = model->getData();
    for(int x = 0; x < data->size(); x++){
        QJsonObject column;
        (dynamic_cast<NumericData*>(data->at(x)->at(0))) ? column["type"] = "Numeric" : column["type"] = "Text";
        QJsonArray dataArray;
        NumericData* tmp = dynamic_cast<NumericData*>(data->at(x)->at(0));
        if(tmp){
            for(int y = 0; y < data->at(x)->size(); y++)
                dataArray.append(static_cast<NumericData*>(data->at(x)->at(y))->getData());
        }
        else{
            TextData* tmp = dynamic_cast<TextData*>(data->at(x)->at(0));
            if(tmp)
                for(int y = 0; y < data->at(x)->size(); y++)
                    dataArray.append(static_cast<TextData*>(data->at(x)->at(y))->getData());
        }
        column["data"] = dataArray;
        jObj.append(column);
    }
}

bool Controller::saveToFile() const
{
    TextBox::somethingWasSelected = false;
    try {
        QString fileName = view->showSaveFile();
        QFile saveFile(fileName);
        if (!saveFile.open(QIODevice::WriteOnly)) {
            throw std::runtime_error("Impossibile aprire il file.");
        }
        QJsonArray sessionObject;
        write(sessionObject);
        saveFile.write(QJsonDocument(sessionObject).toJson());
        return true;
    }  catch (std::runtime_error& e) {
        e.what();
        return false;
    }
}


void Controller::read(const QJsonArray& json)
{
    view->clean();
    model->clean();
    model->loadData(json);
    view->loadData(model->getMatrix());
}

void Controller::loadDataFromFile()
{
    TextBox::somethingWasSelected = false;
    try {
        QString fileName = view->showLoadFile();
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw std::runtime_error("Impossibile aprire il file.");
        }
        QJsonDocument sessionDocument = QJsonDocument::fromJson(file.readAll());
        file.close();
        read(sessionDocument.array());
    }catch (std::runtime_error& e) {
        e.what();
    }
}


void Controller::clearData()
{
    TextBox::somethingWasSelected = false;
        if(getDataMatrixHeigth() > 0){
        int ret = view->showConfirmClear();
        switch (ret) {
          case QMessageBox::Save:
              if(saveToFile())
                break;
              else clearData();
          case QMessageBox::Discard:
              break;
          case QMessageBox::Cancel:
              return;
              break;
          default:
              break;
        }
        view->clean();
        model->clean();
    }
}

void Controller::newFile()
{
    clearData();
}
