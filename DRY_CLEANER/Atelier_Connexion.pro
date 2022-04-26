#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui printsupport
QT       += sql network
QT       +=serialport
QT += svg

CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    arduinomateriel.cpp \
    article.cpp \
    client.cpp \
    dombase.cpp \
    mail/emailaddress.cpp \
    mail/mimeattachment.cpp \
    mail/mimecontentformatter.cpp \
    mail/mimefile.cpp \
    mail/mimehtml.cpp \
    mail/mimeinlinefile.cpp \
    mail/mimemessage.cpp \
    mail/mimemultipart.cpp \
    mail/mimepart.cpp \
    mail/mimetext.cpp \
    mail/quotedprintable.cpp \
    mail/smtpclient.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    materiel.cpp \
    qcustomplot.cpp \
    qr_code.cpp \
    qrcodegen.cpp \
    staff.cpp \
    tabwidget.cpp

HEADERS += \
    arduinomateriel.h \
    article.h \
    client.h \
    defs.h \
    dombase.h \
    mail/SmtpMime \
    mail/emailaddress.h \
    mail/mimeattachment.h \
    mail/mimecontentformatter.h \
    mail/mimefile.h \
    mail/mimehtml.h \
    mail/mimeinlinefile.h \
    mail/mimemessage.h \
    mail/mimemultipart.h \
    mail/mimepart.h \
    mail/mimetext.h \
    mail/quotedprintable.h \
    mail/smtpclient.h \
        mainwindow.h \
    connection.h \
    materiel.h \
    qcustomplot.h \
    qr_code.h \
    qrcodegen.hpp \
    staff.h \
    tabwidget.h

FORMS += \
        mainwindow.ui \
        tabwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
