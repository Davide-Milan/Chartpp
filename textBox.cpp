#include "textBox.h"

TextBox::TextBox(int _x, int _y, bool isNumeric, QWidget* parent, QString text) : QLineEdit(text, parent), x(_x), y(_y) //forse si può fare usando le posizioni nella grid, se no bisogna aggiornarli ogni volta quando se ne eliminano alcuni
{
      connect(this, SIGNAL(textEdited(QString)), this, SLOT(cellEmitter(QString)));
      if(isNumeric && text=="") setText("0");
}

TextBox::~TextBox()
{

}

void TextBox::cellEmitter(QString text)
{
    if(y == -1) emit updateTitle(text, x);
    else emit updateValue(text, x, y);
}

unsigned int TextBox::getX() const {return x;}
unsigned int TextBox::getY() const {return y;}
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
QPair<unsigned int, unsigned int> TextBox::lastSelectedTextBox({0,0});
bool TextBox::somethingWasSelected = false;

QPair<unsigned int, unsigned int> TextBox::getLastSelectedTextBoxCoordinates(){return lastSelectedTextBox;}
