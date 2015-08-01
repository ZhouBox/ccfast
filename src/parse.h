#ifndef PARSE_H
#define PARSE_H

#include "util.h"
#include "analyticparameter.h"

template <typename T>
///
/// \brief The Parse class
/// a logic parse str
/// 分离出来的解析逻辑
///
class Parse
{
public:
    typedef T type_value;
    typedef const T& type_const_value;
    type_const_value parse(const std::string& str_, const std::string& para_, char splitFlag = '&')
    {
        UN_USE(splitFlag);
        static type_value val_;
        return val_;
    }
    static const int buffer_size = 1000;
};

template <>
///
/// \brief The Parse<std::string> class
/// a pares to parse "xxx=xxx&xxx=xxx&...xxx=xxxx" x con`t be '=' or '&'
/// I want to test ance
///
class Parse<std::string>
{
public:
    typedef std::string type_value;
    typedef const std::string& type_const_value;
    static const int buffer_size = 1000;
    type_const_value parse(const std::string& str_, const std::string& para_, char splitFlag = '&')
    {
        static type_value _re(buffer_size, '\0');
        std::string::size_type _pos = str_.find((para_ + '=').c_str());
        if (_pos == std::string::npos)
        {
            _re = "";

        } else
        {
            std::string::size_type _posBegin = _pos + para_.length() + 1;
            std::string::size_type _posValue = str_.find(splitFlag, _posBegin);
            if (_posValue == std::string::npos)
            {
                _re = str_.substr(_posBegin);
            } else
            {
                _re = str_.substr(_posBegin, _posValue - _posBegin);
            }
        }
        return _re;
    }

};

template <>
///
/// \brief The Parse<StringList> class
/// mutil value "xxx=xx,xx,xx&xx=xx&...x=xxx"
/// {xx={xx,}&}
class Parse<StringList>
{
public:
    typedef StringList type_value;
    typedef const StringList& type_const_value;
    static const int buffer_size = 1000;
    type_const_value parse(const std::string& str_, const std::string& para_, char splitFlag = '&')
    {
        static type_value _re;
        static type_value::value_type _temp(buffer_size, '\0');
        _re.clear();
        std::string::size_type _pos = str_.find((para_ + '=').c_str());
        if (_pos == std::string::npos)
        {

        } else
        {
            std::string::size_type _posBegin = _pos + para_.length() + 1;
            std::string::size_type _posValue = str_.find(splitFlag, _posBegin);
            if (_posValue == std::string::npos)
            {
                _temp = str_.substr(_posBegin);
            } else
            {
                _temp = str_.substr(_posBegin, _posValue - _posBegin);
            }
            _re = split(_temp, ',');

        }
        return _re;
    }
};

template<typename T>
struct fast_parse
{
    void parse(const std::string& str_, ParametersValues<T>& pv_, char splitFlag = '&')
    {
        UN_USE(str_);
        UN_USE(pv_);
        UN_USE(splitFlag);
    }
};

template <>
struct fast_parse<std::string>
{
    void parse(const std::string& str_, ParametersValues<std::string>& pv_, char splitFlag = '&')
    {
        StringList _re = split(str_, splitFlag);
        for (auto _n : _re)
        {
            StringList _re1 = split(_n, '=');
            if (_re1.size() == 2)
            {
                ParametersValues<std::string>::type_paraPair _t = {_re1.front(),
                                                                   _re1.back()};
                pv_.insert(_t);
            } else
            {
                if (_re1.size() == 1)
                {
                    ParametersValues<std::string>::type_paraPair _t = {_re1.front(),
                                                                       std::string()};
                    pv_.insert(_t);
                } else
                {
                    throw std::exception();
                }
            }
        }
    }
};






#endif // PARSE_H
