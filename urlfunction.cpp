#include "urlfunction.h"
#include "parse.h"
#include "util.h"
#include "response.h"
#include "logger.h"
#include <json/json.h>
#include <fcgi_stdio.h>



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

///
/// \brief love
/// \param data_
/// method:GET
/// query_string:name=xxx
void love(const std::string &data_)
{
    auto _p = get_parameter_analytic<ParametersValues<std::string> >();
    _p->clear();
    fast_parse<std::string> p;
    _p->registerFastParse(std::bind(&fast_parse<std::string>::parse, &p,
                                 std::placeholders::_1, std::placeholders::_2));

    _p->resetParameterStr(data_);

    try
    {
        _p->fast_analytic();
    } catch(const std::exception &/*ex*/)
    {
        FCGI_puts(Response::json(CODE_ERROR, MESSAGE_ERROR, KVList()).c_str());
        return;
    }
    const ParametersValues<std::string>& _pv = _p->get_result();
    try
    {
        std::stringstream _ss;
        _ss << _pv["boy"] << "  love  " << _pv["girl"];
        FCGI_puts(Response::json(CODE_OK, _ss.str().c_str()).c_str());
    }catch(const std::exception& /*ex1*/)
    {
        FCGI_puts(Response::json(CODE_ERROR, MESSAGE_ERROR, KVList()).c_str());
    }

}
