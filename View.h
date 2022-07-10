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
#include <QAction>
#include <QInputDialog>
#include <QDialog>
#include <QValidator>
#include <QDialogButtonBox>
#include <QColorDialog>
#include <QFormLayout>
#include <QComboBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QCloseEvent>

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
    QPushButton* lineChart;
    QPushButton* barChart;
    QPushButton* pieChart;

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

    void addRow();
    void deleteRow(unsigned int);
    void addColumn(bool);
    void deleteColumn(unsigned int);

    void addFirstCell();
    QString showSelectNewColumnType();
    QString showSaveFile();
    QString showLoadFile();
    void loadData(const Matrix* dataMatrix);
    void clean();
    int showConfirmClear();
    int showColumnSelectionDialogOptionalSingleText(QVector<int>*);
    int showColumnSelectionDialogNumeric(QVector<int>*);

    void drawChart(QChart*);
    void closeChartView();
    QString showChartTitleSelector();
signals:
    void senderPosition(unsigned int, unsigned int);
};
#endif // VIEW_H
