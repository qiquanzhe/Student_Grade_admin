SUBDIRS += \
    Student_Grade_admin.pro

FORMS += \
    mainwindow.ui \
    detailswindow.ui

DISTFILES += \
    Student_Grade_admin.pro.user \
    image/id.png \
    image/password4.png \
    image/sys.ico

HEADERS += \
    mainwindow.h \
    detailswindow.h \
    dboperate.h \
    course.h \
    student.h \
    grade.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    detailswindow.cpp \
    dboperate.cpp \
    course.cpp \
    student.cpp \
    grade.cpp
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RESOURCES += \
    rc.qrc

QT  +=   sql
