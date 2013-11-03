TEMPLATE = app
TARGET = NanoAnalyzer
QT += core \
    gui \
    svg \
    opengl \
    qt3support
HEADERS += GLWidget.h \
    nanoanalyzer.h
SOURCES += GLWidget.cpp \
    main.cpp \
    nanoanalyzer.cpp
FORMS += nanoanalyzer.ui
RESOURCES +=
