CONFIG += c++11

SOURCES += \
    $$PWD/qmfmessagebox.cpp \
    $$PWD/qmfprogressbar.cpp \
    $$PWD/qmfwaitdialog.cpp

HEADERS  += \
    $$PWD/structer.h \
    $$PWD/qmfmessagebox.h \
    $$PWD/qmfprogressbar.h \
    $$PWD/qmfwaitdialog.h

FORMS    += \
    $$PWD/qmfmessagebox.ui \
    $$PWD/qmfprogressbar.ui \
    $$PWD/qmfwaitdialog.ui

RESOURCES += \
    $$PWD/mfwidget.qrc
