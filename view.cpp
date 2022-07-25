#include "view.h"
#include "controller.h"

View::View(QWidget *parent)
    : QWidget(parent), textBoxMatrix(new QVector<QVector<TextBox*>*>), textBoxTitles(new QVector<TextBox*>)
{  
    mainLayout = new QHBoxLayout(this);

    //menus
    addMenus();
    mainLayout->setMenuBar(menuBar);

    //left
    setUpLeftLayout();
    mainLayout->addLayout(leftArea);

    //right (to do)
    setUpRightLayout();
    mainLayout->addLayout(createChartButtons);

    //styling
    setLayout(mainLayout);
    mainLayout->setContentsMargins(10,10,10,10);

}


//only needs to delete the textBox QVectors and their content and the controller, because everything else are QWidgets, whose deletion is handled by the framework already
View::~View()
{
    for(int x = 0; x < textBoxMatrix->size(); x++){
        for(int y=0; y < textBoxMatrix->at(0)->size(); y++){
            delete textBoxMatrix->at(x)->at(y);
        }
        delete textBoxMatrix->at(x);
        delete textBoxTitles->at(x);
        textBoxMatrix->at(x)->clear();
    }
    textBoxMatrix->clear();
    textBoxTitles->clear();

    delete textBoxMatrix;
    delete textBoxTitles;
}

void View::setController(Controller* c)
{
    controller = c;
    linkButtons();
}

void View::addMenus()
{
    menuBar = new QMenuBar(this);
    file = new QMenu("File", menuBar);
    edit = new QMenu("Edit", menuBar);
    view = new QMenu("View", menuBar);
    help = new QMenu("Help", menuBar);

    menuBar->addMenu(file);
    menuBar->addMenu(edit);
    menuBar->addMenu(view);
    menuBar->addMenu(help);

    file->addAction(new QAction(QIcon(":/images/new_file.png"), "New file", file));
    file->addAction(new QAction(QIcon(":/images/open_file.png"), "Open file", file));
    file->addAction(new QAction(QIcon(":/images/save.png"), "Export", file));
    file->addAction(new QAction("Exit", file));
    edit->addAction(new QAction(QIcon(":/images/clear.png"), "Clear all", edit));
    view->addAction(new QAction(QIcon(":/images/line_chart.png"), "Line chart", view));
    view->addAction(new QAction(QIcon(":/images/bar_chart.png"), "Bar chart", view));
    view->addAction(new QAction(QIcon(":/images/pie_chart.png"), "Pie chart", view));
    help->addAction(new QAction(QIcon(":/images/info.png"), "GitHub repo", help));

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

void View::setUpRightLayout()
{
    //create all buttons
    createLineChart = new QPushButton(QIcon(":/images/line_chart.png"), "", this);
    createLineChart->setFixedSize(100,100);
    createLineChart->setIconSize(QSize(100,100));
    createBarChart = new QPushButton(QIcon(":/images/bar_chart.png"), "", this);
    createBarChart->setFixedSize(100,100);
    createBarChart->setIconSize(QSize(100,100));
    createPieChart = new QPushButton(QIcon(":/images/pie_chart.png"), "", this);
    createPieChart->setFixedSize(100,100);
    createPieChart->setIconSize(QSize(100,100));
    closeChart = new QPushButton("Close chart", this);
    closeChart->hide();
    closeChart->setFixedWidth(200);

    //create layout + basic styling
    createChartButtons = new QVBoxLayout();
    createChartButtons->setContentsMargins(0,0,0,0);
    chartViewer = new QVBoxLayout();

    //setup widgets in layouts
    createChartButtons->addWidget(createLineChart);
    createChartButtons->addWidget(createBarChart);
    createChartButtons->addWidget(createPieChart);
    chartViewer->addWidget(closeChart);
    chartViewer->setAlignment(closeChart, Qt::AlignCenter);
}

//connects default buttons to their controller slots
void View::linkButtons()
{
    //menu
    menuBar->connect(file->actions()[0], SIGNAL(triggered()), controller, SLOT(newFile()));
    menuBar->connect(file->actions()[1], SIGNAL(triggered()), controller, SLOT(loadDataFromFile()));
    menuBar->connect(file->actions()[2], SIGNAL(triggered()), controller, SLOT(saveToFile()));
    menuBar->connect(edit->actions()[0], SIGNAL(triggered()), controller, SLOT(clearData()));
    menuBar->connect(view->actions()[0], SIGNAL(triggered()), controller, SLOT(lineChart()));
    menuBar->connect(view->actions()[1], SIGNAL(triggered()), controller, SLOT(barChart()));
    menuBar->connect(view->actions()[2], SIGNAL(triggered()), controller, SLOT(pieChart()));
    menuBar->connect(help->actions()[0], SIGNAL(triggered()), controller, SLOT(openRepositoryLink()));

    //left area
    connect(loadDataButton, SIGNAL(clicked()), controller, SLOT(loadDataFromFile()));
    connect(saveDataButton, SIGNAL(clicked()), controller, SLOT(saveToFile()));
    connect(addRowButton, SIGNAL(clicked()), controller, SLOT(addRow()));
    connect(addColumnButton, SIGNAL(clicked()), controller, SLOT(addColumn()));
    connect(deleteRowButton, SIGNAL(clicked()), controller, SLOT(deleteRow()));
    connect(deleteColumnButton, SIGNAL(clicked()), controller, SLOT(deleteColumn()));

    //right area
    connect(createLineChart, SIGNAL(clicked()), controller, SLOT(lineChart()));
    connect(createBarChart, SIGNAL(clicked()), controller, SLOT(barChart()));
    connect(createPieChart, SIGNAL(clicked()), controller, SLOT(pieChart()));
    connect(closeChart, SIGNAL(clicked()), controller, SLOT(deleteChart()));
}

//connects textbox to their corresponding controller slot, distinguishing between titles and data textboxes
void View::connectNewTextBox(TextBox* tmp)
{
    if(tmp->getY() == -1) connect(tmp, SIGNAL(updateTitle(QString, unsigned int)), controller, SLOT(updateTitle(QString, unsigned int)));
    else connect(tmp, SIGNAL(updateValue(QString, unsigned int, unsigned int)), controller, SLOT(updateValue(QString, unsigned int, unsigned int)));
}

QString View::showSelectNewColumnType()
{
    QStringList items;
    items << tr("Numeric") << tr("Text");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Add column"), tr("Select type of data for new column:"), items, 0, false, &ok);
    if(ok)  return item;
    return "";
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


int View::showColumnSelectionDialogOptionalSingleText(QVector<int>* indexes, const QString& msg)
{
    QStringList items;
    for(unsigned int col = 0; col < controller->getDataMatrixWidth(); col++) if(indexes->contains(col)) items.append(QString::number(col+1) + " - " + textBoxTitles->at(col)->text());
    bool ok;
    QString selection= QInputDialog::getItem(this, tr("Chart creation"), msg, items, 0, false, &ok);
    if(ok)
        return (selection.mid(0, selection.indexOf(" "))).toInt() - 1;  //-1 because im adding one in the option string to make it more user friendly
    else
        throw bool(false);
}


int View::showColumnSelectionDialogNumeric(QVector<int>* indexes)
{
    QStringList items;
    for(unsigned int col = 0; col < controller->getDataMatrixWidth(); col++) if(indexes->contains(col)) items.append(QString::number(col+1) + " - " + textBoxTitles->at(col)->text());
    bool ok;
    QString selection= QInputDialog::getItem(this, tr("Chart creation"), tr("Select a numeric data column"), items, 0, false, &ok);
    if(ok)
        return (selection.mid(0, selection.indexOf(" "))).toInt() - 1;  //-1 because im adding one in the option string to make it more user friendly
    else
        throw bool(false);
}

//dialog to input title for chart
QString View::showChartTitleSelector()
{
    bool ok;
    QString title= QInputDialog::getText(this, tr("Chart creation"), tr("Insert a title for your chart"), QLineEdit::Normal, "New Chart", &ok);
    if(ok)
        return title;
    else{
        throw bool(false);
    }
}

//resets the table view
void View::clean()
{
    for(unsigned int x = 0; x < controller->getDataMatrixWidth(); x++){
        for(unsigned int y=0; y < controller->getDataMatrixHeigth(); y++){
            delete textBoxMatrix->at(x)->at(y);
        }
        textBoxMatrix->at(x)->clear();
        delete textBoxMatrix->at(x);
        delete textBoxTitles->at(x);
    }
    textBoxMatrix->clear();
    textBoxTitles->clear();
    closeChartView();
}

void View::addRow()
{
    unsigned int width = controller->getDataMatrixWidth();

    if(width==1 && controller->getDataMatrixHeigth()==1)
        textBoxMatrix->append(new QVector<TextBox*>());      //array is empty so I initialize it with a new internal array
    int y = controller->getDataMatrixHeigth() - 1;
    for(unsigned int x = 0; x < width; x++){
        bool isNumeric = controller->isNumeric(x);
        if(y>0){    //moves title cell down one row to keep on bottom of the columns
            QWidget* aux = dataArea->itemAtPosition(y,x)->widget();
            dataArea->removeWidget(aux);
            dataArea->addWidget(aux,y+1,x);
        }
        TextBox* tmp = new TextBox(x,y,isNumeric,scrollWidget);
        tmp->setObjectName(QString::number(x) + "," + QString::number(y));
        connectNewTextBox(tmp);
        dataArea->addWidget(tmp, y, x);
        textBoxMatrix->at(x)->append(tmp);
    }
    if(width==1 && controller->getDataMatrixHeigth()==1){        //first title
        TextBox* tmpTitle = new TextBox(0,-1, false, scrollWidget);
        tmpTitle->setPlaceholderText("column 0");
        tmpTitle->setObjectName("0,-1");
        if(controller->isNumeric(0)) tmpTitle->setStyleSheet("QLineEdit { background: rgba(237, 104, 162, 0.5);}");
        else
            tmpTitle->setStyleSheet("QLineEdit { background: rgba(232, 227, 74, 0.75);}");
        textBoxTitles->append(tmpTitle); //adds new TextBox* for titles
        connectNewTextBox(tmpTitle);
        dataArea->addWidget(tmpTitle, width, 0);
    }
}

void View::addColumn(bool isNumeric)
{
    unsigned int size = controller->getDataMatrixHeigth();
    QVector<TextBox*>* tmpArray = new QVector<TextBox*>();
    int x = controller->getDataMatrixWidth() - 1;

    TextBox* tmpTitle = new TextBox(x,-1, false, scrollWidget);
    tmpTitle->setPlaceholderText("column " + QString::number(x));
    tmpTitle->setObjectName(QString::number(x) + ",-1");
    if(isNumeric)
        tmpTitle->setStyleSheet("QLineEdit { background: rgba(237, 104, 162, 0.5);}");
    else
        tmpTitle->setStyleSheet("QLineEdit { background: rgba(232, 227, 74, 0.75);}");
    connectNewTextBox(tmpTitle);
    textBoxTitles->append(tmpTitle); //adds new TextBox* for titles
    dataArea->addWidget(tmpTitle,size, x);

    for(unsigned int y = 0; y < size; y++){
        TextBox* tmp = new TextBox(x,y,isNumeric,scrollWidget);
        tmp->setObjectName(QString::number(x) + "," + QString::number(y));
        connectNewTextBox(tmp);
        dataArea->addWidget(tmp, y, x);
        tmpArray->append(tmp);
    }
    textBoxMatrix->append(tmpArray); //adds new QVector<TextBox*>
}

//called after clean, thus no need for checks on textBoxMatrix content
void View::loadData(const Matrix* dataMatrix)
{
    for(unsigned int x=0; x < controller->getDataMatrixWidth(); x++){
        QVector<TextBox*>* tmpColumn = new QVector<TextBox*>;
        textBoxMatrix->append(tmpColumn);
        bool isNumeric = controller->isNumeric(x);        
        for(unsigned int y=0; y < controller->getDataMatrixHeigth(); y++){
            TextBox* tmp;
            if(isNumeric)
                tmp = new TextBox(x, y, true, scrollWidget, QString::number(static_cast<NumericData*>(dataMatrix->getDataAt(x,y))->getData())); //static cast is safe because of the previous dynamic cast
            else
                tmp = new TextBox(x, y, false, scrollWidget, static_cast<TextData*>(dataMatrix->getDataAt(x,y))->getData()); //static cast is safe because of the previous dynamic cast
            connectNewTextBox(tmp);
            dataArea->addWidget(tmp, y, x);
            tmpColumn->append(tmp);
        }
        TextBox* tmpTitle = new TextBox(x,-1, false, scrollWidget, dataMatrix->getTitle(x));
        tmpTitle->setPlaceholderText("column " + QString::number(x));
        tmpTitle->setObjectName(QString::number(x) + ",-1");
        if(isNumeric)
            tmpTitle->setStyleSheet("QLineEdit { background: rgba(237, 104, 162, 0.5);}");
        else
            tmpTitle->setStyleSheet("QLineEdit { background: rgba(232, 227, 74, 0.75);}");
        connectNewTextBox(tmpTitle);
        textBoxTitles->append(tmpTitle); //adds new TextBox* for titles
        dataArea->addWidget(tmpTitle,controller->getDataMatrixHeigth(), x);
    }
}


//hides creation buttons and shows the chart created by the model
void View::drawChart(QChart* chart)
{
    closeChart->show();
    createLineChart->hide();
    createBarChart->hide();
    createPieChart->hide();
    mainLayout->removeItem(createChartButtons);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartViewer->addWidget(chartView);
    mainLayout->addLayout(chartViewer);
    view->setDisabled(true);    //disables view menu to prevent multiple graphs from being displayed
}

//closes and deletes chart view, shows chart creation buttons
void View::closeChartView()
{
    if(chartView != nullptr && chartViewer->parent() == mainLayout){
    createLineChart->show();
    createBarChart->show();
    createPieChart->show();
    mainLayout->removeItem(chartViewer);
    chartViewer->removeWidget(chartView);
    closeChart->hide();
    delete chartView;
    chartView = nullptr;
    mainLayout->addLayout(createChartButtons);
    view->setDisabled(false);   //re-enables view menu
    }
}
