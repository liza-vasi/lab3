QT       += core gui sql charts printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bargraph.cpp \
    colorexporter.cpp \
    grayexporter.cpp \
    ioc_container.cpp \
    linegraph.cpp \
    main.cpp \
    mainwindow.cpp \
    sqlitereader.cpp \
    #test_sqlite.cpp \
    themewidget.cpp

HEADERS += \
    bargraph.h \
    colorexporter.h \
    datapoint.h \
    grayexporter.h \
    idatareader.h \
    iexporter.h \
    igraph.h \
    ioc_container.h \
    linegraph.h \
    mainwindow.h \
    sqlitereader.h \
    themewidget.h

FORMS += \
    #mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
