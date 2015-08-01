TEMPLATE = app
CONFIG += console release 
CONFIG -= app_bundle
CONFIG -= qt
TARGET = ccfast
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXX = g++-4.8

SOURCES += src/main.cpp \
    tpl/redis-cplusplus-client/anet.c \
    tpl/md5/md5.cpp \
    src/util.cpp \
    src/urlfunction.cpp \
    src/fcgiprogram.cpp \
    src/response.cpp \
    src/systemparameter.cpp \
    src/ccfastprogram.cpp \
    src/randomnumbergenerator.cpp \
    src/redisimplpolicy.cpp \
    src/stringbuilder.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    src/api.h \
    src/analyticparameter.h \
    src/typedefs.h \
    src/fcgiprogram.h \
    src/fcgiworker.h \
    src/util.h \
    src/parse.h \
    src/urlroute.h \
    src/ncstudiofcgi.h \
    src/systemresource.h \
    src/urlfunction.h \
    src/response.h \
    src/sendemail.h \
    src/systemparameter.h \
    src/logger.h \
    src/ccfastprogram.h \
    src/sessionmanager.h \
    src/randomnumbergenerator.h \
    tpl/redis-cplusplus-client/fmacros.h \
    tpl/redis-cplusplus-client/anet.h\
    tpl/redis-cplusplus-client/redisclient.h \
    tpl/md5/md5.h \
    src/redisimplpolicy.h \
    src/stringbuilder.h



OBJECTS_DIR = ./obj
DESTDIR = ./bin

LIBS += -lfcgi \
        -ljsoncpp \
        -lpthread \
        -lboost_system \
        -lboost_thread \
        -lmysqlpp \
        -lboost_date_time

DEFINES += MYSQLPP_MYSQL_HEADERS_BURIED _GLIBCXX_PERMIT_BACKWARD_HASH

DISTFILES += \
    ccfast_install/ccfast/mysql_redis.conf \
    ccfast_install/ccfast/sendmail.py \
    ccfast_install/install

