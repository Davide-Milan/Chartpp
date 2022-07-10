#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QLineEdit>

class TextBox : public QLineEdit
{
    Q_OBJECT
private:
    int x, y;
    bool isNumericText;
    static QPair<int,int> lastSelectedTextBox;
public:
    TextBox(int, int, bool = false, QWidget* = nullptr, QString = "");
    virtual ~TextBox();

    static QPair<int,int> getLastSelectedTextBoxCoordinates();
    static bool somethingWasSelected;

    int getX() const;
    int getY() const;
    bool isNumeric() const;

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
signals:
    void updateTitle(QString, unsigned int);
    void updateValue(QString, unsigned int, unsigned int);
    void test(QPair<unsigned int, unsigned int>);
private slots:
    void cellEmitter(QString);
};

#endif // TEXTBOX_H
