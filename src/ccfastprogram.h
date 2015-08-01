#ifndef CcFastProgram_H
#define CcFastProgram_H

#include "fcgiprogram.h"
#include "sessionmanager.h"
#include "redisimplpolicy.h"

class CcFastProgram : public FcgiProgram
{
public:
    CcFastProgram();
    virtual ~CcFastProgram() {}
    ///
    /// \brief init 在请求处理循环前,作一些初始化工作
    ///
    void init();
    ///
    /// \brief process 处理请求
    ///
    void process();
    ///
    /// \brief end 处理循环退出,作一些收尾工作
    ///
    void end();
private:
    
};

#endif // CcFastProgram_H
