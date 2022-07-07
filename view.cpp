#include "view.h"
#include "controller.h"

View::View(QWidget *parent)
    : QWidget(parent)
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

    file->addAction(new QAction("Open", file));
    file->addAction(new QAction("Save", file));
    file->addAction(new QAction("Close", file));
    edit->addAction(new QAction("Undo", edit));
    edit->addAction(new QAction("Redo", edit));
    view->addAction(new QAction("Zoom in", view));
    view->addAction(new QAction("Zoom out", view));

    menuBar->resize(4000,20);       //makes it as large as possible
    menuBar->connect(file->actions()[2], SIGNAL(triggered()), this, SLOT(close()));
}

void View::setUpLeftLayout()
{
    //create buttons
    loadDataButton = new QPushButton("Load file", this);
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
    connect(addRowButton, SIGNAL(clicked()), controller, SLOT(addRow()));
    connect(addColumnButton, SIGNAL(clicked()), controller, SLOT(addColumn()));
    connect(deleteRowButton, SIGNAL(clicked()), controller, SLOT(deleteRow()));
    connect(deleteColumnButton, SIGNAL(clicked()), controller, SLOT(deleteColumn()));
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
    textBoxMatrix.append(new QVector<TextBox*>(1, tmp)); //adds new QVector<TextBox*> with tmp
}

QString View::showSelectNewColumnType()
{
    QStringList items;
    items << tr("Numeric") << tr("Text");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                         tr("Select type of data for new column:"), items, 0, false, &ok);
    if(ok)
        return item;
    return "";
}

void View::addRow()
{
    unsigned int size = controller->getDataMatrixWidth();
    if (size > 0){
        if(size==1 && controller->getDataMatrixHeigth()==1) textBoxMatrix.append(new QVector<TextBox*>());      //array is empty so I initialize it with a new internal array
        for(unsigned int x = 0; x < size; x++){
            int y = controller->getDataMatrixHeigth() - 1;         
            TextBox* tmp = new TextBox(x,y,scrollWidget);
            tmp->setObjectName(QString::number(x) + "," + QString::number(y));
            connectNewTextBox(tmp);
            dataArea->addWidget(tmp, y, x);            
            textBoxMatrix[x]->append(tmp);
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
            TextBox* tmp= textBoxMatrix[x]->at(row);
            textBoxMatrix[x]->remove(row);
            delete tmp;
        }
        if(textBoxMatrix[0]->size()>0){
            for(unsigned int y = row; y < controller->getDataMatrixHeigth()-1; y++){
                for(unsigned int x = 0; x < controller->getDataMatrixWidth(); x++)
                    textBoxMatrix[x]->at(y)->decreaseY();
            }
        }
        else{
            for(int x = 0; x < controller->getDataMatrixWidth(); x++){
                QVector<TextBox*>* tmp = textBoxMatrix[x];
                textBoxMatrix.remove(x);
                delete tmp;
            }
        }
        QTextStream(stdout) << "TextBoxMatrix width: " + QString::number(textBoxMatrix.size()) << endl;
        QTextStream(stdout) << "TextBoxMatrix heigth: " + QString::number(textBoxMatrix[0]->size()) << endl;
    }
    else return;
}

void View::addColumn()
{
    unsigned int size = controller->getDataMatrixHeigth();
    if (size > 0){
        QVector<TextBox*>* tmpArray = new QVector<TextBox*>();
        textBoxMatrix.append(tmpArray); //adds new QVector<TextBox*>
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
            delete textBoxMatrix[col]->at(y);
        }
        QVector<TextBox*>* tmp= textBoxMatrix[col];
        textBoxMatrix.remove(col);
        delete tmp;

        if(textBoxMatrix.size()>0){
            for(unsigned int x = col; x < controller->getDataMatrixWidth()-1; x++){
                for(unsigned int y = 0; y < controller->getDataMatrixHeigth(); y++)
                    textBoxMatrix[x]->at(y)->decreaseX();
            }
        }
    }
    else return;
}
