TEMPLATE = app
TARGET = NanoAnalyzer
QT += core \
    gui \
    svg \
    opengl
HEADERS += ArcBall.h \
    GLWidget.h \
    nanoanalyzer.h
SOURCES += ArcBall.cpp \
    GLWidget.cpp \
    main.cpp \
    nanoanalyzer.cpp
FORMS += nanoanalyzer.ui
CONFIG += static
