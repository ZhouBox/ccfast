#ifndef FCGIPROGRAM_H
#define FCGIPROGRAM_H

#include "analyticparameter.h"
#include "typedefs.h"
///
/// \brief The FcgiProgram class a abstract class for a fcgi program
/// init fcgi init body
/// process fcgi work with client request --> logic work
/// end do something when fcgi quit
///
/// T is parameter/value->value
///
class FcgiProgram
{
public:
    FcgiProgram();
    virtual ~FcgiProgram() = 0;
    virtual void init() = 0;
    virtual void process() = 0;
    virtual void end() = 0;
protected:
    string_hash m_string_hash;
};


#endif // FCGIPROGRAM_H
