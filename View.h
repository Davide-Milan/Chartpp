#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

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
    QMenuBar* menuBar;
    QMenu* file;
    QMenu* edit;
    QMenu* view;

    Controller* controller;

    QVBoxLayout* auxLayout; //used to get mainlayout underneath menubar without having them overlapped
    QHBoxLayout* mainLayout;

    //left layout
    QVBoxLayout* leftArea;
    QVBoxLayout* dataArea;
    QScrollArea* dataAreaScroll;
    QHBoxLayout* leftButtons;

    QPushButton* saveDataButton;
    QPushButton* loadDataButton;
    QPushButton* addRowButton;
    QPushButton* deleteRowButton;
    QPushButton* addColumnButton;
    QPushButton* deleteColumnButton;

    void addMenus();
    void setUpLeftLayout();

public:
    View(QWidget *parent = nullptr);
    ~View();
};
#endif // VIEW_H
