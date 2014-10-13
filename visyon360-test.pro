#-------------------------------------------------
#
# Project created by QtCreator 2014-10-09T00:53:36
#
#-------------------------------------------------

QT       += core opengl gui multimedia

macx{
    CONFIG += c++11
    QMAKE_CXXFLAGS += -stdlib=libc++
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visyon360-test
TEMPLATE = app


SOURCES += main.cc\
    meshutils.cc \
    mesh.cc \
    timer.cc \
    mainglwindow.cc \
    videotextureplayer.cc

HEADERS  += \
    meshutils.h \
    mesh.h \
    timer.h \
    mainglwindow.h \
    videotextureplayer.h


OTHER_FILES += \
    media/003.jpg


macx {
    AssetFiles.path = Contents/MacOS/
    AssetFiles.files = $$files(media/*)
    QMAKE_BUNDLE_DATA += AssetFiles
}
