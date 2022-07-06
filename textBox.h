#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QLineEdit>

class TextBox : public QLineEdit
{
public:
    TextBox(QString = "", QWidget* = nullptr);
};

#endif // TEXTBOX_H
