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
You can add as many rows and columns as you want.

Of course you can also delete entire rows and columns: in order to do so, you have to first select a column by clicking on any data or title cell and then click "Delete column" or click on "Delete row", but in this case, clicking on a column's title won't work for selecting a row of course, because you can only delete a row of data, not a row of titles.
If you click on anything else before than "Delete row/column" you will see an error message asking you to select a column/row first.
![no column selected](https://user-images.githubusercontent.com/95528465/182441121-9bde8037-4d9d-4728-9e00-2cff0b1473a8.png)

You can also load data from a JSON file by clicking on "Open file" and selecting the file from the file selection dialog; in the same way you can also export your data by clicking on "Export" and creating a JSON file.
![load data](https://user-images.githubusercontent.com/95528465/182432807-98cf62cb-26a9-4de1-8ba9-b51c7a7a499f.png)

Once you have created your columns and inserted all the data you need, you can proceed by clicking on one of the 3 charts buttons on the right: a series of dialogs will pop up to guide you on selecting the columns you want to use in order to create the chart.
![chart creation](https://user-images.githubusercontent.com/95528465/182433694-e5893a9e-55af-4bbf-802b-d3fc165efdf7.png)

Every chart has its own type of data that must be selected in order to create it:
### Line chart
You can only create one type of Line chart, using only numeric columns, how many as you want: every column will be represented by a line

### Bar chart
You can create one type of Bar chart: by selecting a text column whose data will be used to name every bar of the chart, otherwise the names will be just an incrementing number starting from 1.
Every data from a numeric column will be repesented by a bar whose height corresponds to the value of the data itself; every column selected will make for a section, grouping bars together.

### Pie chart
You can create two types of Pie charts:
For the first one select only a text column: the chart will display how many times each text data is present in the column.
For the second one either select a text column or not, and only one numeric column: the chart will display the value of the data in the numeric column, labeled by the data in the same row in the text column selected, or by an incrementing number.

The project only required to implement 3 types of charts, but many more could be implemented

##Now you know how to use this software, happy charting
