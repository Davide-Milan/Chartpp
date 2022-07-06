#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QLineEdit>
#include <QTextStream>
class TextBox : public QLineEdit
{
    Q_OBJECT
private:
    unsigned int x, y;
public:
    TextBox(unsigned int, unsigned int, QWidget* = nullptr, QString = "");
    virtual ~TextBox();
    unsigned int getX() const;
    unsigned int getY() const;
    void decreaseX();
    void decreaseY();

public slots:
    void cellEmitter(QString);
};

#endif // TEXTBOX_H
