#include "textBox.h"

TextBox::TextBox(int _x, int _y, bool _isNumeric, QWidget* parent, QString text) : QLineEdit(text, parent), x(_x), y(_y), isNumericText(_isNumeric)
{
      connect(this, SIGNAL(textEdited(QString)), this, SLOT(cellEmitter(QString)));
      if(isNumericText && text=="") setText("0");
}

TextBox::~TextBox()
{

}

void TextBox::cellEmitter(QString text)
{
    if(y == -1) emit updateTitle(text, x);
    else emit updateValue(text, x, y);
}

int TextBox::getX() const {return x;}
int TextBox::getY() const {return y;}

bool TextBox::isNumeric() const{return isNumericText;}
void TextBox::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    if(y != -1)setStyleSheet("QLineEdit { background: rgb(255, 255, 255); }");
}


void TextBox::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    lastSelectedTextBox = {x,y};
    if(y != -1){
        somethingWasSelected = true;
        setStyleSheet("QLineEdit { background: rgba(32, 191, 227, 0.4); }");
    }
    else somethingWasSelected = false;
}

//STATIC FIELDS AND FUNCTIONS
QPair<int,int> TextBox::lastSelectedTextBox({0,0});
bool TextBox::somethingWasSelected = false;

QPair<int, int> TextBox::getLastSelectedTextBoxCoordinates(){return lastSelectedTextBox;}
