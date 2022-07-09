#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QLineEdit>
#include <QTextStream>

class TextBox : public QLineEdit
{
    Q_OBJECT
private:
    int x, y;
    bool numeric;
    static QPair<unsigned int, unsigned int> lastSelectedTextBox;
public:
    TextBox(int, int, bool = false, QWidget* = nullptr, QString = "");
    virtual ~TextBox();

    static QPair<unsigned int, unsigned int> getLastSelectedTextBoxCoordinates();
    static bool somethingWasSelected;

    unsigned int getX() const;
    unsigned int getY() const;

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
