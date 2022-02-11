QT       += core gui
LIBS += -L$$PWD/ -lUSB3102A
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    caiji.cpp \
    instruction.cpp \
    main.cpp \
    qcustomplot.cpp \
    sampleforce.cpp \
    testmax.cpp \
    widget.cpp

HEADERS += \
    USB3102A.h \
    USB3102ARSV.h \
    caiji.h \
    instruction.h \
    qcustomplot.h \
    sampleforce.h \
    testmax.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target