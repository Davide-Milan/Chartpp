#include "view.h"

View::View(QWidget *parent)
    : QWidget(parent)
{  
    mainLayout = new QHBoxLayout(this);

    //menus
    addMenus();
    mainLayout->addMenuBar(menuBar);

    //left
    setUpLeftLayout();
    mainLayout->addLayout(leftArea);

    //right (to do)


    //styling
    mainLayout->setContentsMargins(10,0,10,10);
}

View::~View()
{
}

void MainWindow::addMenus()
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

void MainWindow::setUpLeftLayout()
{
    //create buttons
    loadDataButton = new QPushButton("Load file", this);
    saveDataButton = new QPushButton("Export", this);
    addRowButton = new QPushButton("Add row", this);
    deleteRowButton = new QPushButton("Delete row", this);
    addColumnButton = new QPushButton("Add column", this);
    deleteColumnButton = new QPushButton("Delete column", this);

    //create layouts + basic styling
    dataArea = new QVBoxLayout(this);
    dataArea->setSpacing(0);   //sets space between cells
    dataAreaScroll = new QScrollArea();
    dataAreaScroll->
    QWidget* spacer = new QWidget(this); spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //trick for empty space to keep buttons on the bottom side of the dataArea
    leftButtons = new QHBoxLayout(this);
    leftArea = new QVBoxLayout(this);
    leftArea->setContentsMargins(0,0,0,0);

    //setup layout hierarchy
    leftArea->addLayout(dataArea);
    leftArea->addWidget(spacer);
    leftArea->addLayout(leftButtons);

    //setup widgets in layouts
    leftButtons->addWidget(loadDataButton);
    leftButtons->addWidget(saveDataButton);
    leftButtons->addWidget(addRowButton);
    leftButtons->addWidget(deleteRowButton);
    leftButtons->addWidget(addColumnButton);
    leftButtons->addWidget(deleteColumnButton);
}
