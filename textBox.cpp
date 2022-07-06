#include "textBox.h"

TextBox::TextBox(unsigned int _x, unsigned int _y, QWidget* parent, QString text) : QLineEdit(text, parent), x(_x), y(_y) //forse si può fare usando le posizioni nella grid, se no bisogna aggiornarli ogni volta quando se ne eliminano alcuni
{
      connect(this, SIGNAL(textChanged(QString)), this, SLOT(cellEmitter(QString)));
//    connect(this, SIGNAL(textEdited(QString)), this, SLOT(cellEmitter(QString)));
}

TextBox::~TextBox()
{

}

//void TextBox::cellEmitter(QString text){
//    emit updateValue(text, sender()->pare);
//}

void TextBox::cellEmitter(QString text){
    QTextStream(stdout) << text;
}

unsigned int TextBox::getX() const {return x;}
unsigned int TextBox::getY() const {return y;}
void TextBox::decreaseX() {x--;}
void TextBox::decreaseY() {y--;}
