/*
 * This file is part of the Chartpp project for the OOP course at the University of Padua (Italy).
 * The project consists in making a software capable of providing the user the capability of:
 *      -managing data (creation, deletion) via a graphic interface
 *      -saving and loading this data to and from a file
 *      -using this data to create at least 3 different types of charts to be displayed
 *
 * What should be done:
 *      -create a friendly and simple user interface to do everything using the framework Qt
 *      -separate logic and GUI
 *      -inheritance with custom class gerarchy and polymorphism must be used
 *      -students are free to handle everything else as they prefer, including the type of data to be used to make the chars and how to store the data via saving to a file
 * 
 * My own implementation of the project, called "Chartpp" (which is a play on words about the programming language used C++ => Cpp => Chartpp), utilizes JSON to save and load data
 * and lets users input either numeric or textual data in order to create and display 3 different types of charts (line chart, bar chart and pie chart) in a very easy way.
 * 
 * 
 * 
 * Author: Davide Milan
 * ---------------------------------------------------------------- 
 * Programming Language: C++
 * ---------------------------------------------------------------- 
 * Framework: Qt  
 * ---------------------------------------------------------------- 
 * Pattern used: MVC (MVP)
 * ----------------------------------------------------------------  
 * GitHub repo: https://github.com/Davide-Milan/Chartpp
 * ----------------------------------------------------------------  
 * Year: 2022
 * ----------------------------------------------------------------  
 */

#include "view.h"

#include <QApplication>

#include "model.h"
#include "view.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QString("Chart++"));
    Model m;
    View v;
    Controller c;

    c.setModel(&m);
    c.setView(&v);
    v.setController(&c);

    v.setFixedSize(1000, 600);
    v.show();
    return a.exec();
}
