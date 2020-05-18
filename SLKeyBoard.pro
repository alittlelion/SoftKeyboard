QT += core  gui widgets

TEMPLATE = lib
TARGET = SLKeyBoard

DEFINES += SLKEYBOARD_LIB
LIBS += -L"."
DEPENDPATH += .



# Default rules for deployment.

!isEmpty(target.path): INSTALLS += target


include(SLKeyBoard.pri)

RESOURCES += \
    slkeyboard.qrc
