#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

#include "textBox.h"

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
    QVector<QVector<TextBox*>> textBoxMatrix;
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

    void addMenus();
    void setUpLeftLayout();
    void linkButtons();
public:
    View(QWidget *parent = nullptr);
    ~View();
    void setController(Controller *);

    void addRow();
    void deleteRow();
    void addColumn();
    void deleteColumn();

    void addFirstCell();

signals:
    void senderPosition(unsigned int, unsigned int);
};
#endif // VIEW_H
