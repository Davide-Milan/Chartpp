#include "textBox.h"

TextBox::TextBox(QString text, /*unsigned int x, unsigned int y,*/ QWidget* parent) : QLineEdit(text, parent) //forse si può fare usando le posizioni nella grid, se no bisogna aggiornarli ogni volta quando se ne eliminano alcuni
{
    connect(this, SIGNAL(textEdited(QString)), this, SLOT(cellEmitter(int, int)));
}

void TextBox::cellEmitter(){

}
