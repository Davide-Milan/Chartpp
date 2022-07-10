QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barChart.cpp \
    chart.cpp \
    controller.cpp \
    data.cpp \
    lineChart.cpp \
    main.cpp \
    matrix.cpp \
    model.cpp \
    numericData.cpp \
    pieChart.cpp \
    textBox.cpp \
    textData.cpp \
    view.cpp

HEADERS += \
    barChart.h \
    chart.h \
    controller.h \
    data.h \
    lineChart.h \
    matrix.h \
    model.h \
    numericData.h \
    pieChart.h \
    textBox.h \
    textData.h \
    view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
