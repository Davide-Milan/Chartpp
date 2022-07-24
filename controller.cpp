#include "controller.h"

Controller::Controller(QObject *parent) : QObject{parent}
{

}

Controller::~Controller()
{
}

void Controller::setModel(Model *m) {model = m;}

void Controller::setView(View *v) { view = v;}

unsigned int Controller::getDataMatrixWidth() const {return model->getDataMatrixWidth();}

unsigned int Controller::getDataMatrixHeigth() const {return model->getDataMatrixHeigth();}

Matrix *Controller::getDataMatrix() const {return model->getMatrix();}


void Controller::updateValue(QString text, unsigned int x, unsigned int y){model->updateDataMatrixValue(text, x, y);}


void Controller::updateTitle(QString text, unsigned int x){model->updateTitle(text, x);}


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

        view->clean();
        model->clean();
        model->loadData(sessionDocument.array());
        view->loadData(model->getMatrix());
    }catch (std::runtime_error& e) {
        e.what();
    }
}


bool Controller::saveToFile() const
{
    TextBox::somethingWasSelected = false;
    try {
        QString fileName = view->showSaveFile();
        model->writeFile(fileName);
        return true;
    }  catch (std::runtime_error& e) {
        e.what();
        return false;
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


void Controller::newFile(){clearData();}


bool Controller::anyCellSelected(bool row)
{
    if(!TextBox::somethingWasSelected){
        QMessageBox msgBox;
        row ? msgBox.setText("No row selected") : msgBox.setText("No column selected");
        msgBox.exec();
        return false;
    }
    return true;
}

bool Controller::isNumeric(unsigned int col) const{return model->isNumeric(col);}


//SLOTS
void Controller::addRow()
{
    int width = getDataMatrixWidth();

    bool isNumeric = false;
    if(width == 0){
        QString selection = view->showSelectNewColumnType();
        if (selection.isEmpty())return;
        else if(selection == "Numeric") isNumeric = true;
        model->addColumnData(isNumeric); //this way it handles the Numeric or Text choice without adding a new function
    }
    else
        model->addRowData();
    view->addRow();
}

void Controller::deleteRow()
{
    if(TextBox::getLastSelectedTextBoxCoordinates().second == -1) TextBox::somethingWasSelected = false;    //if the last selected TextBox is a title it will prevent it from deleting all the titles
    if(!anyCellSelected(true)) return;    

    TextBox::somethingWasSelected = false;
    unsigned int size = getDataMatrixHeigth();
    if (size > 0){
        unsigned int row = TextBox::getLastSelectedTextBoxCoordinates().second;
        view->clean();
        model->deleteRowData(row);
        view->loadData(getDataMatrix());
    }
}

void Controller::addColumn()
{
    TextBox::somethingWasSelected = false;
    bool isNumeric = false;
    QString selection = view->showSelectNewColumnType();
    if (selection.isEmpty())
        return;
    if(selection == "Numeric") isNumeric = true;
    model->addColumnData(isNumeric);
    view->addColumn(isNumeric);
}

void Controller::lineChart()
{
    dataIsEmpty();
    if(model->getNumberOfNumerics() < 1){
        QMessageBox msgBox;
        msgBox.setText("Insert at least one numeric column first");
        msgBox.exec();
    }
    else{
        QString title;
        try{
            title = view->showChartTitleSelector();
        }
        catch(bool){ //if the dialog for title selection is closed it will interrupt the method
            return;
        }

        QVector<int> chosenNumericIndexes;
        QVector<int>* numericDataIndexesLeft = model->getNumericDataIndexes();
        bool choose = true;
        while(choose){
            if(numericDataIndexesLeft->size() > 0){
                int numericIndex;
                try{
                    numericIndex = view->showColumnSelectionDialogNumeric(numericDataIndexesLeft);
                }
                catch(bool){
                    return;
                }
                if(numericIndex >= 0){
                    chosenNumericIndexes.append(numericIndex);
                    numericDataIndexesLeft->erase(numericDataIndexesLeft->begin() + numericDataIndexesLeft->indexOf(numericIndex));
                }
                else choose = false;
            }
            else choose = false;
        }
        delete numericDataIndexesLeft;

        if(chosenNumericIndexes.size() < 1){
            QMessageBox msgBox;
            msgBox.setText("No data was selected, try again");
            msgBox.exec();
        }
        else{
            view->drawChart((model->createLineChart(title, chosenNumericIndexes))->draw());
        }
    }
}

void Controller::barChart()
{
    dataIsEmpty();
    if(model->getNumberOfNumerics() < 1){
        QMessageBox msgBox;
        msgBox.setText("Insert at least one numeric column first");
        msgBox.exec();
    }
    else{
        QString title;
        try{
            title = view->showChartTitleSelector();
        }
        catch(bool){
            return;
        }
        int chosenTextIndex = -1;
        QVector<int> chosenNumericIndexes;
        if(model->getNumberOfTexts() > 0){
            QVector<int>* textDataIndexes = model->getTextDataIndexes();
            try{
                chosenTextIndex = view->showColumnSelectionDialogOptionalSingleText(textDataIndexes, tr("Select an OPTIONAL text data column"));
            }
            catch(bool){    //nothing happens beacause the text column is optional in this chart
            }
            delete textDataIndexes;
        }
        QVector<int>* numericDataIndexesLeft = model->getNumericDataIndexes();
        bool choose = true;
        while(choose){
            if(numericDataIndexesLeft->size() > 0){
                int numericIndex;
                try{
                    numericIndex = view->showColumnSelectionDialogNumeric(numericDataIndexesLeft);
                }
                catch(bool){
                    return;
                }
                if(numericIndex >= 0){
                    chosenNumericIndexes.append(numericIndex);
                    numericDataIndexesLeft->erase(numericDataIndexesLeft->begin() + numericDataIndexesLeft->indexOf(numericIndex));
                }
                else choose = false;
            }
            else choose = false;
        }
        delete numericDataIndexesLeft;

        if(chosenNumericIndexes.size() < 1){
            QMessageBox msgBox;
            msgBox.setText("No data was selected, try again");
            msgBox.exec();
        }
        else{
            view->drawChart((model->createBarChart(title, chosenNumericIndexes, chosenTextIndex))->draw());
        }

    }
}

bool Controller::dataIsEmpty()
{
    TextBox::somethingWasSelected = false;
    if(getDataMatrixWidth() < 1){
        QMessageBox msgBox;
        msgBox.setText("There's no data to select from");
        msgBox.exec();
        return true;
    }
    return false;
}

void Controller::pieChart()
{   
    if(dataIsEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Insert at least one column of any type first");
        msgBox.exec();
    }
    else{
        QString title;
        try{
            title = view->showChartTitleSelector();
        }
        catch(bool){
            return;
        }
        int chosenTextIndex = -1;
        if(model->getNumberOfTexts() > 0){
            QVector<int>* textDataIndexes = model->getTextDataIndexes();
            try{
                chosenTextIndex = view->showColumnSelectionDialogOptionalSingleText(textDataIndexes, tr("Select one text column"));
            }
            catch(bool){
            }
            delete textDataIndexes;
        }
        int numericIndex = -1;
        if(model->getNumberOfNumerics() > 0){
            try{
                numericIndex = view->showColumnSelectionDialogNumeric(model->getNumericDataIndexes());
            }
            catch(bool){
            }
        }
        if(numericIndex >= 0 || chosenTextIndex >= 0)
            view->drawChart((model->createPieChart(title, numericIndex, chosenTextIndex))->draw());
        else{
                QMessageBox msgBox;
                msgBox.setText("No data was selected, try again");
                msgBox.exec();
        }
    }
}

void Controller::deleteColumn()
{
    if(!anyCellSelected(false)) return;

    TextBox::somethingWasSelected = false;
    unsigned int size = getDataMatrixWidth();
    if (size > 0){
        unsigned int col = TextBox::getLastSelectedTextBoxCoordinates().first;
        view->clean();
        model->deleteColumnData(col);
        view->loadData(getDataMatrix());
    }
}

void Controller::deleteChart()
{
    view->closeChartView();
    model->deleteChart();
}

bool Controller::openRepositoryLink()
{
    try{
        bool ok = QDesktopServices::openUrl(QUrl("https://github.com/Davide-Milan/Chartpp", QUrl::TolerantMode));
        if(!ok)
            throw bool(false);
        else
            return true;
    }
    catch(bool){
        QMessageBox msgBox;
        msgBox.setText("Something went wrong, we couldn't open the GitHub repository on a browser");
        msgBox.exec();
        return false;
    }
}
