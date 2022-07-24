#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QLineEdit>

class TextBox : public QLineEdit
{
    Q_OBJECT
private:
    int x, y;
    bool isNumericText; //not used for something yet, but could be used in the future for ensuring the right type of input from the user
    static QPair<int,int> lastSelectedTextBox;
public:
    TextBox(int, int, bool = false, QWidget* = nullptr, QString = "");
    virtual ~TextBox();

    static QPair<int,int> getLastSelectedTextBoxCoordinates();
    static bool somethingWasSelected;

    int getX() const;
    int getY() const;
    bool isNumeric() const;


    /**
     * @brief overrides QLineEdit's focusInEvent method: activates when a TextBox receives focus by clicking on it or tabbing into it.
     * Sets lastSelectedTextBox <int,int> with the selected TextBox's x and y and somethingWasSelected is set to true;
     * If the TextBox is one of the columns titles it won't be saved and somethingWasSelected gets set to false tho.
     * Also the background of the data TextBox gets colored (doesn't do anything on titles TextBoxes).
    */
    void focusInEvent(QFocusEvent *event) override;

    /**
     * @brief overrides QLineEdit's focusOutEvent method: activates when a TextBox loses focus.
     * If the caller is a data TextBox the background gets resetted.
    */
    void focusOutEvent(QFocusEvent *event) override;
signals:

    // signal used by the controller to update the Model's Matrix's title of the right column
    void updateTitle(QString, unsigned int);
    // signal used by the controller to update the Model's Matrix's value at the right coordinates in the dataMatrix
    void updateValue(QString, unsigned int, unsigned int);
private slots:

    // custom slot used to call a custom signal with multiple parameters
    void cellEmitter(QString);
};

#endif // TEXTBOX_H
