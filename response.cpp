#include "response.h"

Response::Response()
{
}


Response* Response::instance()
{
    static Response _s_response;
    return &_s_response;
}
///
/// \brief Response::json
/// \param code_ 响应码
/// \param message_ 信息
/// \param data_ 响应数据
/// \return
///
/// {
///     "code":int,
///     "message":"",
///     "data":{
///     }
/// }

const std::string& Response::json(int code_, const std::string& message_, const KVList &data_)
{
    static std::string _strjson_re(m_s_buffer_size, '\0');
    static Json::FastWriter _json_fastwriter;
    static Json::Value _root;
    static Json::Value _data;
    _root["code"] = code_;
    _root["message"] = message_;
    for (auto _n : data_)
    {
        _data[_n.first] = _n.second;
    }

    _root["data"] = _data;

    _strjson_re = _json_fastwriter.write(_root);
    _root.clear();
    _data.clear();
    return _strjson_re;
}
