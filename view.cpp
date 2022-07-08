#include "view.h"
#include "controller.h"

View::View(QWidget *parent)
    : QWidget(parent), textBoxMatrix(new QVector<QVector<TextBox*>*>)
{  
    mainLayout = new QHBoxLayout(this);

    //menus
    addMenus();
    mainLayout->setMenuBar(menuBar);

    //left
    setUpLeftLayout();
    mainLayout->addLayout(leftArea);

    //right (to do)


    //styling
    setLayout(mainLayout);
    mainLayout->setContentsMargins(10,0,10,10);
}

View::~View()
{
}

void View::setController(Controller* c) {
    controller = c;
    linkButtons();
}

void View::addMenus()
{
    menuBar = new QMenuBar(this);
    file = new QMenu("File", menuBar);
    edit = new QMenu("Edit", menuBar);
    view = new QMenu("View", menuBar);

    menuBar->addMenu(file);
    menuBar->addMenu(edit);
    menuBar->addMenu(view);

    file->addAction(new QAction("New file", file));
    file->addAction(new QAction("Open file", file));
    file->addAction(new QAction("Export", file));
    file->addAction(new QAction("Close", file));
    edit->addAction(new QAction("Clear all", edit));
//    edit->addAction(new QAction("Undo", edit));
//    edit->addAction(new QAction("Redo", edit));
    view->addAction(new QAction("Zoom in", view));
    view->addAction(new QAction("Zoom out", view));

    menuBar->resize(4000,20);       //makes it as large as possible
    menuBar->connect(file->actions()[3], SIGNAL(triggered()), this, SLOT(close()));
}

void View::setUpLeftLayout()
{
    //create buttons
    loadDataButton = new QPushButton("Open file", this);
    saveDataButton = new QPushButton("Export", this);
    addRowButton = new QPushButton("Add row", this);
    deleteRowButton = new QPushButton("Delete row", this);
    addColumnButton = new QPushButton("Add column", this);
    deleteColumnButton = new QPushButton("Delete column", this);

    //create layouts + basic styling
    scrollWidget = new QWidget(this);
    dataArea = new QGridLayout(scrollWidget);
//    for(int i = 0; i < 15; i++){
//        dataArea->addWidget(new TextBox(scrollWidget),i,i);
//    }

    dataArea->setSpacing(0);   //sets space between cells    
    dataArea->setSizeConstraint(QLayout::SetMinAndMaxSize);

    scrollWidget->setLayout(dataArea);
    scrollWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    dataAreaScroll = new QScrollArea(this);
    dataAreaScroll->setWidget(scrollWidget);
    dataAreaScroll->setMinimumHeight(500);
    dataAreaScroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    leftButtons = new QHBoxLayout();
    leftArea = new QVBoxLayout();
    leftArea->setContentsMargins(0,0,0,0);

    //setup layout hierarchy
    leftArea->addWidget(dataAreaScroll);
    leftArea->addLayout(leftButtons);

    //setup widgets in layouts
    leftButtons->addWidget(loadDataButton);
    leftButtons->addWidget(saveDataButton);
    leftButtons->addWidget(addRowButton);
    leftButtons->addWidget(deleteRowButton);
    leftButtons->addWidget(addColumnButton);
    leftButtons->addWidget(deleteColumnButton);

}


void View::linkButtons()
{
    connect(loadDataButton, SIGNAL(clicked()), controller, SLOT(loadDataFromFile()));
    connect(saveDataButton, SIGNAL(clicked()), controller, SLOT(saveToFile()));
    connect(addRowButton, SIGNAL(clicked()), controller, SLOT(addRow()));
    connect(addColumnButton, SIGNAL(clicked()), controller, SLOT(addColumn()));
    connect(deleteRowButton, SIGNAL(clicked()), controller, SLOT(deleteRow()));
    connect(deleteColumnButton, SIGNAL(clicked()), controller, SLOT(deleteColumn()));

    menuBar->connect(file->actions()[0], SIGNAL(triggered()), controller, SLOT(newFile()));
    menuBar->connect(file->actions()[1], SIGNAL(triggered()), controller, SLOT(loadDataFromFile()));
    menuBar->connect(file->actions()[2], SIGNAL(triggered()), controller, SLOT(saveToFile()));
    menuBar->connect(edit->actions()[0], SIGNAL(triggered()), controller, SLOT(clearData()));
}

void View::connectNewTextBox(TextBox* tmp)
{
    connect(tmp, SIGNAL(updateValue(QString, unsigned int, unsigned int)), controller, SLOT(updateValue(QString, unsigned int, unsigned int)));
    connect(tmp, SIGNAL(test(QPair<unsigned int, unsigned int>)), controller, SLOT(test(QPair<unsigned int, unsigned int>)));
}

void View::addFirstCell()
{
    TextBox* tmp = new TextBox(0,0,scrollWidget);
    tmp->setObjectName("0,0");
    connectNewTextBox(tmp);
    dataArea->addWidget(tmp,0,0);
    textBoxMatrix->append(new QVector<TextBox*>(1, tmp)); //adds new QVector<TextBox*> with tmp
}

QString View::showSelectNewColumnType()
{
    QStringList items;
    items << tr("Numeric") << tr("Text");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Add column"),
                                         tr("Select type of data for new column:"), items, 0, false, &ok);
    if(ok)
        return item;
    return "";
}

void View::addRow()
{
    unsigned int size = controller->getDataMatrixWidth();
    if (size > 0){
        if(size==1 && controller->getDataMatrixHeigth()==1) textBoxMatrix->append(new QVector<TextBox*>());      //array is empty so I initialize it with a new internal array
        for(unsigned int x = 0; x < size; x++){
            int y = controller->getDataMatrixHeigth() - 1;         
            TextBox* tmp = new TextBox(x,y,scrollWidget);
            tmp->setObjectName(QString::number(x) + "," + QString::number(y));
            connectNewTextBox(tmp);
            dataArea->addWidget(tmp, y, x);            
            textBoxMatrix->at(x)->append(tmp);
        }
    }
    else{
        addFirstCell();
    }
}

void View::deleteRow(unsigned int row)
{
    unsigned int size = controller->getDataMatrixWidth();
    if (size > 0){
        for(unsigned int x = 0; x < size; x++){
            TextBox* tmp= textBoxMatrix->at(x)->at(row);
            dataArea->removeWidget(textBoxMatrix->at(x)->at(row));
            textBoxMatrix->at(x)->erase(textBoxMatrix->at(x)->begin() + row);
            delete tmp;
//            if(row < controller->getDataMatrixHeigth()-1)
//                controller->shiftRowsOnDelete(x,row);
        }
        if(textBoxMatrix->at(0)->size()>0){
            for(unsigned int y = row; y < controller->getDataMatrixHeigth()-1; y++){
                for(unsigned int x = 0; x < controller->getDataMatrixWidth(); x++){
                    textBoxMatrix->at(x)->at(y)->decreaseY();
                    textBoxMatrix->at(x)->at(y)->setObjectName(QString::number(x) + "," + QString::number(y));
                }
            }
        }
        else{
            for(int x = 0; x < controller->getDataMatrixWidth(); x++){
                QVector<TextBox*>* tmp = textBoxMatrix->at(x);
                textBoxMatrix->remove(x);
                delete tmp;
            }
        }
        qDebug() << "TextBoxMatrix width: " + QString::number(textBoxMatrix->size()) << endl;
        qDebug() << "TextBoxMatrix heigth: " + QString::number(textBoxMatrix->at(0)->size()) << endl;
    }
    else return;
}

void View::addColumn()
{
    unsigned int size = controller->getDataMatrixHeigth();
    if (size > 0){
        QVector<TextBox*>* tmpArray = new QVector<TextBox*>();
        textBoxMatrix->append(tmpArray); //adds new QVector<TextBox*>
        for(unsigned int y = 0; y < size; y++){
            int x = controller->getDataMatrixWidth() - 1;
            TextBox* tmp = new TextBox(x,y,scrollWidget);
            tmp->setObjectName(QString::number(x) + "," + QString::number(y));
            connectNewTextBox(tmp);
            dataArea->addWidget(tmp, y, x);
            tmpArray->append(tmp);
        }
    }
    else{
        addFirstCell();
    }
}

void View::deleteColumn(unsigned int col)
{
    unsigned int size = controller->getDataMatrixHeigth();
    if (size > 0){
        for(unsigned int y = 0; y < size; y++){
            dataArea->removeWidget(textBoxMatrix->at(col)->at(y));
            delete textBoxMatrix->at(col)->at(y);
        }
        QVector<TextBox*>* tmp= textBoxMatrix->at(col);
        textBoxMatrix->erase(textBoxMatrix->begin() + col);
        delete tmp;
//        if(col < controller->getDataMatrixWidth()-1)
//            controller->shiftColumnsOnDelete(col);

        if(textBoxMatrix->size()>0){
            for(unsigned int x = col; x < controller->getDataMatrixWidth()-1; x++){
                for(unsigned int y = 0; y < controller->getDataMatrixHeigth(); y++){
                    textBoxMatrix->at(x)->at(y)->decreaseX();
                    textBoxMatrix->at(x)->at(y)->setObjectName(QString::number(x) + "," + QString::number(y));
                }
            }
        }
    }
    else return;
}

void View::shiftRowsOnDelete(unsigned int x, unsigned int row)
{

}


void View::shiftColumnsOnDelete(unsigned int col)
{
//    for(unsigned int _col = col; _col < controller->getDataMatrixWidth()-1; _col++){
//        qDebug() << QString::number(_col);
//        textBoxMatrix->at(_col) = new QVector<TextBox*>/*textBoxMatrix->at(col+1)*/;
//    }
    //textBoxMatrix->remove(col);
}

QString View::showSaveFile()
{
    QFileDialog saveDialog(this);
    QString fileName = saveDialog.getSaveFileName(
        this,
        tr("Save data in a json file"), "",
        tr(".json (*.json)")
    );
    if (fileName == "")
       throw std::runtime_error("Nessun file selezionato: operazione annullata.");
    if (!fileName.endsWith(".json"))
        fileName += ".json";
    return fileName;
}

QString View::showLoadFile()
{
    QFileDialog loadDialog(this);
    QString fileName = loadDialog.getOpenFileName(
        this,
        tr("Load data from a json file"), "",
        tr(".json (*.json)")
    );
    if (fileName == "")
       throw std::runtime_error("Nessun file selezionato: operazione annullata.");
    if (!fileName.endsWith(".json"))
        fileName += ".json";
    return fileName;
}

void View::loadData(const Matrix* dataMatrix)   //called after clean, thus no need for checks on textBoxMatrix content
{
    for(int x=0; x < controller->getDataMatrixWidth(); x++){
        QVector<TextBox*>* tmpColumn = new QVector<TextBox*>;
        textBoxMatrix->append(tmpColumn);
        if(dynamic_cast<NumericData*>(dataMatrix->getDataAt(x))){
            for(int y=0; y < controller->getDataMatrixHeigth(); y++){
                TextBox* tmp = new TextBox(x, y, scrollWidget, QString::number(static_cast<NumericData*>(dataMatrix->getDataAt(x,y))->getData())); //static cast is safe because of the previous dynamic cast
                connectNewTextBox(tmp);
                dataArea->addWidget(tmp, y, x);
                tmpColumn->append(tmp);
            }
        }
        else{
            for(int y=0; y < controller->getDataMatrixHeigth(); y++){
                TextBox* tmp = new TextBox(x, y, scrollWidget, static_cast<TextData*>(dataMatrix->getDataAt(x,y))->getData()); //static cast is safe because of the previous dynamic cast
                connectNewTextBox(tmp);
                dataArea->addWidget(tmp, y, x);
                tmpColumn->append(tmp);
            }
        }
    }
}

void View::clean()
{
    for(int x = 0; x < controller->getDataMatrixWidth(); x++){
        for(int y=0; y < controller->getDataMatrixHeigth(); y++){
            delete textBoxMatrix->at(x)->at(y);
        }
        textBoxMatrix->at(x)->clear();
        delete textBoxMatrix->at(x);
    }
    textBoxMatrix->clear();
}

int View::showConfirmClear()
{
    QMessageBox msgBox;
    msgBox.setText("You're about to erase everything");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    return msgBox.exec();
}
