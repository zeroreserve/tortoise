!include("../Common/retroshare_plugin.pri"):error("Could not include file ../Common/retroshare_plugin.pri")

CONFIG += qt \
    uic \
    qrc \
    resources

SOURCES = \
    p3TortoiseRS.cpp \
    RSTortoiseItems.cpp \
    TortoiseDialog.cpp \
    TortoisePlugin.cpp

LIBS += -lsqlite3

DEFINES += ZR_TESTNET

HEADERS = \
    p3TortoiseRS.h \
    RSTortoiseItems.h \
    TortoiseDialog.h \
    TortoisePlugin.h

FORMS = \
    TortoiseDialog.ui

TARGET = Tortoise

RESOURCES = \
    Tortoise_images.qrc
