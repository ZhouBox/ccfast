#ifndef API_H
#define API_H

#include "analyticparameter.h"
#include "parse.h"
#include "sessionmanager.h"

template <typename T>
ParameterAnalytic<T>* get_parameter_analytic();
template <typename T>
Parse<T>* get_parse();


template <typename T>
ParameterAnalytic<T>* get_parameter_analytic()
{
    static ParameterAnalytic<T> _s_pa;
    return &_s_pa;
}

template <typename T>
Parse<T>* get_parse()
{
    static Parse<T> _s_parse;
    return &_s_parse;
}

template<typename T>
SessionManager<T>* get_session_manager()
{
    static SessionManager<T> _s_sm;
    return &_s_sm;
}

#endif //API_H