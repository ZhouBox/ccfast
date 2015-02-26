TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = ccfast

SOURCES += main.cpp \
    util.cpp \
    urlfunction.cpp \
    fcgiprogram.cpp \
    response.cpp \
    systemparameter.cpp \
    ccfastprogram.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    analyticparameter.h \
    typedefs.h \
    fcgiprogram.h \
    fcgiworker.h \
    ObjectCreator.h \
    util.h \
    parse.h \
    urlroute.h \
    ncstudiofcgi.h \
    systemresource.h \
    urlfunction.h \
    response.h \
    sendemail.h \
    systemparameter.h \
    logger.h \
    ccfastprogram.h


LIBS += -lfcgi \
        -ljsoncpp \
        -lredisclient \
        -lpthread \
        -lboost_system \
        -lboost_thread \
        -lmysqlpp

DEFINES += MYSQLPP_MYSQL_HEADERS_BURIED _GLIBCXX_PERMIT_BACKWARD_HASH

