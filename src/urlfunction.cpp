#include "urlfunction.h"
#include "response.h"
#include "logger.h"
#include "api.h"
#include "redisimplpolicy.h"
#include "stringbuilder.h"
#include <json/json.h>
#include <fcgi_stdio.h>





///
/// \brief love
/// \param data_
/// method:GET
/// query_string:boy=xxx&girl=xxx
void love(const std::string &data_)
{

    auto pSessionManager = get_session_manager<RedisImplPolicy>();
    pSessionManager->flushSessionId();
    const std::string& session = pSessionManager->getCurrentSessionId();
    if (session.empty()) {
        pSessionManager->createSessionId();
        pSessionManager->set("key", "value");
    } 
    else {
        bool had = pSessionManager->had();
        if (!had) {
            pSessionManager->createSessionId();
            pSessionManager->set("key", "value");
        }
    }

    // _2stringVector headers;
    // headers.push_back(_2string("Set-Cookie", (std::string(SESSIONID) + "=") + pSessionManager->getCurrentSessionId()));
    // headers.push_back(_2string("Content-type","application/json; charset=UTF-8\r\n\r\n"));

    // putsHeaders(headers);

    StringBuilder ss;
    ss << "Set-Cookie:" << SESSIONID << "=" << pSessionManager->getCurrentSessionId()  << ";";

    FCGI_puts(ss.toString().c_str());

    ss.clear();
    ss << "Content-type:application/json; charset=UTF-8\r\n\r\n";

    FCGI_puts(ss.toString().c_str());

    auto _p = get_parameter_analytic<ParametersValues<std::string> >();
    _p->clear();
    fast_parse<std::string> p;
    _p->registerFastParse(std::bind(&fast_parse<std::string>::parse, &p,
                                 std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    _p->resetParameterStr(data_);
    _p->setSplitFlag('&');
    try
    {
        _p->fast_analytic();
    } catch(std::exception &/*ex*/)
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
    }catch(std::exception& /*ex1*/)
    {
        FCGI_puts(Response::json(CODE_ERROR, MESSAGE_ERROR, KVList()).c_str());
    }

}
