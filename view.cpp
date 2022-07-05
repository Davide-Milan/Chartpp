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
    for(int i = 0; i < 5; i++){
        dataArea->addWidget(new QLineEdit(scrollWidget),i,i);
    }

    dataArea->setSpacing(0);   //sets space between cells
    scrollWidget->setLayout(dataArea);
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

void View::addRow()
{
    unsigned int size = controller->getDataMatrixWidth();
    if (size != 0){
        QTextStream(stdout) << "iffffffffff" << endl;
        for(unsigned int x = 0; x <= size; x++){
            int y = controller->getDataMatrixHeigth() - 1;
            QLineEdit* tmp = new QLineEdit(scrollWidget);
            tmp->setObjectName(QString::number(x).append(",").append(QString::number(y)));
            dataArea->addWidget(tmp, y, x);
        }
    }
    else{
        QTextStream(stdout) << "elseeeee" << endl;
        QLineEdit* tmp = new QLineEdit(scrollWidget);
        tmp->setObjectName("0,0");
        QTextStream(stdout) << QString::number(dataArea->count()) << endl;
        dataArea->addWidget(tmp,6,6);
        QTextStream(stdout) << QString::number(dataArea->count()) << endl;
    }
}
void View::deleteRow()
{

}
void View::addColumn()
{

}
void View::deleteColumn()
{

}
