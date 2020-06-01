QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Translator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# Output directory
CONFIG(debug, debug|release) {
    output = debug
}
CONFIG(release, debug|release) {
    output = release
}
DESTDIR     = bin
OBJECTS_DIR = $$output
MOC_DIR     = $$output
RCC_DIR     = $$output
UI_DIR      = $$output

SOURCES += main.cpp \
    languagemanager.cpp \
    languagetest.cpp \
    preferencesdialog.cpp \
    preferences.cpp


HEADERS += \
    languagemanager.h \
    languagetest.h \
    preferencesdialog.h \
    preferences.h


FORMS += \
    preferencesdialog.ui


RESOURCES +=

TRANSLATIONS += tiled_zh_CN.ts\
                tiled_en.ts

#include(util/util.pri)
