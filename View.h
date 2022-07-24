#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

#include "textBox.h"
#include "matrix.h"
#include "chart.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QScrollBar>
#include <QChartView>
#include <QtCharts>
#include <QInputDialog>
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>

class Controller;

class View : public QWidget
{
    Q_OBJECT

private:   
    QVector<QVector<TextBox*>*>* textBoxMatrix;
    QVector<TextBox*>* textBoxTitles;

    QMenuBar* menuBar;
    QMenu* file;
    QMenu* edit;
    QMenu* view;
    QMenu* help;

    Controller* controller;

    QHBoxLayout* mainLayout;

    //left layout
    QVBoxLayout* leftArea;
    QScrollArea* dataAreaScroll;
    QWidget* scrollWidget;
    QGridLayout* dataArea;
    QHBoxLayout* leftButtons;

    QPushButton* saveDataButton;
    QPushButton* loadDataButton;
    QPushButton* addRowButton;
    QPushButton* deleteRowButton;
    QPushButton* addColumnButton;
    QPushButton* deleteColumnButton;


    //right layout
    QVBoxLayout* createChartButtons;
    QPushButton* createLineChart;
    QPushButton* createBarChart;
    QPushButton* createPieChart;

    QVBoxLayout* chartViewer;
    QChartView* chartView;
    QPushButton* closeChart;

    void addMenus();
    void setUpLeftLayout();
    void linkButtons();
    void connectNewTextBox(TextBox* tmp);
    void setUpRightLayout();

public:
    View(QWidget *parent = nullptr);
    ~View();
    void setController(Controller *);

    //TEXTBOX GRID RELATED METHODS
    void addRow();
    void deleteRow(unsigned int);
    void addColumn(bool);
    void deleteColumn(unsigned int);
    void loadData(const Matrix* dataMatrix);  //given a Matrix, genereates the TextBox grid and loads every cell with the right data from the Matrix.
    void clean();  //resets the view

    //USER DIALOG INTERACTION METHODS
    QString showSelectNewColumnType(); //input dialog to choose the type of data of the new column (Text or Numeric)
    QString showSaveFile(); //file dialog to choose a JSON file to save data into
    QString showLoadFile(); //file dialog to choose a JSON file to import data from
    int showConfirmClear(); //message box dialog asking to confirm the removal of all data
    int showColumnSelectionDialogOptionalSingleText(QVector<int>*, const QString&); //input dialog for asking to select a textData column, if needed by the type of chart selected
    int showColumnSelectionDialogNumeric(QVector<int>*); //input dialog for asking to select a numericData column, not optional

    //CHART RELATED METHODS
    void drawChart(QChart*);
    void closeChartView();
    QString showChartTitleSelector();
signals:
    void senderPosition(unsigned int, unsigned int);
};
#endif // VIEW_H
