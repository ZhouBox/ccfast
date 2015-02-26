#include "util.h"
#include "systemparameter.h"
#include <fcgi_stdio.h>

StringList& operator<<(StringList& slist_, const std::string& str_)
{
    slist_.push_back(str_);
    return slist_;
}

StringList split(const std::string& str_, char c_)
{
    std::string _buff{""};
    StringList _t;

    for(auto _n:str_)
    {
        if(_n != c_)
        {
            _buff += _n;
        }else
            if(_n == c_ && _buff != "")
            {
                _t.push_back(_buff);
                _buff = "";
            }
    }
    if(_buff != "") _t.push_back(_buff);

    return _t;
}

const char* g_cstrRedisHost = "localhost";

boost::shared_ptr<redis::client> get_redis_client()
{
    const SystemParameter* _sp = SystemParameter::instance();
    const char* cstr_host = getenv("REDIS_HOST");
    std::string str_host = _sp->m_redis_server;//g_cstrRedisHost;
    if (cstr_host)
    {
        str_host = cstr_host;
    }
    return boost::shared_ptr<redis::client>(new redis::client(str_host));
}


int string2int(const std::string& str_)
{
    std::stringstream _ss;
    _ss << str_;
    int _re;
    _ss >> _re;
    return _re;
}

std::string int2string(int id_)
{
    std::stringstream _ss;
    _ss << id_;
    return _ss.str();
}

std::string& format_send_email(std::string &message_)
{
    std::string& _re = message_;
    for (size_t i = 0;i != _re.length(); ++i)
    {
        if (_re[i] == '\'')
        {
            _re[i] = '`';
        }
    }
    return _re;
}

char g_host_name_buffer[256];

const char* get_hostname()
{
    gethostname(g_host_name_buffer, sizeof(g_host_name_buffer));
    return g_host_name_buffer;
}

char g_content_buffer[CONTENT_LEN];

const char* get_content()
{
    const char* _re = NULL;
    char* _content_len = getenv("CONTENT_LENGTH");
    long _len = 0;
    if (_content_len != NULL && strlen(_content_len) != 0)
    {
        _len = strtol(_content_len, &_content_len, 10);
        if (*_content_len)
        {
            _len = 0;
        }
    } else {

    }

    if (_len > 0)
    {
        int _i;
        int _ch;
        for (_i = 0; _i < _len; ++_i)
        {
            if ((_ch = getchar()) < 0)
            {
                break;
            }
            g_content_buffer[_i] = _ch;
        }
        if (_i == _len)
        {
            g_content_buffer[_len] = '\0';
            _re = g_content_buffer;
        }

    } else
    {

    }
    return _re;
}


