# Chartpp - Chart++


This is my submission for the project of the OOP course at the University of Padua (Italy).
The project consists in making a software that gives the user the capability of:
*     managing data (creation, deletion) via a graphic interface
*     saving and loading this data to and from a file
*     using this data to create at least 3 different types of charts to be displayed

What should be done:
*     -create a friendly and simple user interface to do everything, using the framework Qt
*     -separate logic and GUI
*     -inheritance with custom class gerarchy/gerarchies and polymorphism must be used
*     -students are free to handle everything else as they prefer, including the type of data to be used to make the charts and how to store the data via saving to a file

My own implementation of the project, called "Chartpp" (which is a play on words about the programming language used C++ => Cpp => Chartpp), utilizes JSON to save and load data
and lets users input either numeric or textual data in order to create and display 3 different types of charts (line chart, bar chart and pie chart) in a very easy way.



Author:  Davide Milan
---------------------------------------------------------------- 
Programming Language: C++
---------------------------------------------------------------- 
Framework: Qt  
---------------------------------------------------------------- 
Pattern used: MVC (MVP)
----------------------------------------------------------------   
Year: 2022
----------------------------------------------------------------  

## How to use this software:
### Build on Linux
From the terminal, while inside the source code folder:
*	mkdir build
*	cd build
*	qmake ..
*	make
*	./Chartpp

This is the interface:
![chartpp infographic](https://user-images.githubusercontent.com/95528465/182260905-8bc5e589-cc9d-4b67-97f5-f647160b7c2c.png)

Using the data buttons you can start by creating the first column by clicking either "add row" or "add column":
![new column](https://user-images.githubusercontent.com/95528465/182431017-218519c7-94a2-48b4-aa2e-8415fb600ce9.png)
Select either Numeric, to create a column that handles numeric data, or Text, to create a column that handles text data: the type selected will let you create specific types of charts later.

You can also load data from a JSON file by clicking on "Open file" and selecting the file from the file selection dialog; in the same way you can also export your data by clicking on "Export" and creating a JSON file.
![load data](https://user-images.githubusercontent.com/95528465/182432807-98cf62cb-26a9-4de1-8ba9-b51c7a7a499f.png)

Once you have created your columns and inserted all the data you need, you can proceed by clicking on one of the 3 charts buttons on the right: a series of dialogs will pop up to guide you on selecting the columns you want to use in order to create the chart.
![chart creation](https://user-images.githubusercontent.com/95528465/182433694-e5893a9e-55af-4bbf-802b-d3fc165efdf7.png)

Every chart has its own type of data that must be selected in order to create it:
### Line chart

### Bar chart

### Pie chart
