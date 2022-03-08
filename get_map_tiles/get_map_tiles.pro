QT       += core gui network quickwidgets qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    http.cpp \
    log_thread.cpp \
    main.cpp \
    mainwindow.cpp \
    map_preview.cpp \
    rec_qmldata.cpp \
    thread_loop.cpp

HEADERS += \
    http.h \
    log_thread.h \
    mainwindow.h \
    map_preview.h \
    rec_qmldata.h \
    thread_loop.h

FORMS += \
    mainwindow.ui \
    map_preview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    qml.qrc
