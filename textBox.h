#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QLineEdit>

class TextBox : public QLineEdit
{
    Q_OBJECT
private:

public:
    int x, y;
    TextBox(int, int, QWidget* = nullptr, QString = "");
    virtual ~TextBox();

    static QPair<unsigned int, unsigned int> lastSelectedTextBox;
    static QPair<unsigned int, unsigned int> getLastSelectedTextBoxCoordinates();
    static bool somethingWasSelected;

    unsigned int getX() const;
    unsigned int getY() const;
    void decreaseX();
    void decreaseY();

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
signals:
    void updateValue(QString, unsigned int, unsigned int);
    void test(QPair<unsigned int, unsigned int>);
private slots:
    void cellEmitter(QString);
public slots:

};

#endif // TEXTBOX_H
