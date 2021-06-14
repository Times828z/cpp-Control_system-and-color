QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcourse.cpp \
    addstudent.cpp \
    addteacher.cpp \
    datachange.cpp \
    delInfo.cpp \
    importscore.cpp \
    main.cpp \
    mainwindow.cpp \
    student.cpp \
    student_course.cpp \
    system.cpp \
    teacher.cpp \
    teacher_addscore.cpp \
    teacher_search.cpp

HEADERS += \
    addcourse.h \
    addstudent.h \
    addteacher.h \
    datachange.h \
    delInfo.h \
    importscore.h \
    mainwindow.h \
    student.h \
    student_course.h \
    system.h \
    teacher.h \
    teacher_addscore.h \
    teacher_search.h

FORMS += \
    addcourse.ui \
    addstudent.ui \
    addteacher.ui \
    datachange.ui \
    delInfo.ui \
    importscore.ui \
    mainwindow.ui \
    student.ui \
    student_course.ui \
    system.ui \
    teacher.ui \
    teacher_addscore.ui \
    teacher_search.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    a.qrc


