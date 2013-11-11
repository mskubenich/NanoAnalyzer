TEMPLATE = app
TARGET = NanoAnalyzer
QT += core gui svg opengl
HEADERS += GLWidget.h nanoanalyzer.h
SOURCES += GLWidget.cpp main.cpp nanoanalyzer.cpp
FORMS += nanoanalyzer.ui
CONFIG += static
