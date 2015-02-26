#include "systemparameter.h"
#include <iostream>
#include <string.h>

const char* g_strconf = "/etc/ccfast/mysql_redis.conf";


SystemParameter* SystemParameter::instance()
{
    static SystemParameter _s_sys_parameter;
    return &_s_sys_parameter;
}

SystemParameter::SystemParameter():
    m_mysql_server("localhost"),
    m_mysql_port(3306),
    m_mysql_db(""),
    m_mysql_user(""),
    m_mysql_pwd(""),
    m_redis_server("localhost"),
    m_redis_port(6379),
    m_redis_pwd("")
{
}

bool SystemParameter::load()
{
    bool _re = false;
    std::fstream _in;
    _in.open(g_strconf, std::ios_base::in);
    if (_in.is_open())
    {
        Json::Reader _jsonReader;
        Json::Value _jsonRoot;
        if (_jsonReader.parse(_in, _jsonRoot, false))
        {
            m_mysql_server = _jsonRoot["mysql_server"].asString();
            m_mysql_port = _jsonRoot["mysql_port"].asInt();
            m_mysql_db = _jsonRoot["db"].asString();
            m_mysql_user = _jsonRoot["mysql_user"].asString();
            m_mysql_pwd = _jsonRoot["mysql_pwd"].asString();

            m_redis_server = _jsonRoot["redis_server"].asString();
            m_redis_port = _jsonRoot["redis_port"].asInt();
            m_redis_pwd = _jsonRoot["redis_pwd"].asString();
            if (m_mysql_server.empty() || m_mysql_db.empty() || m_mysql_user.empty() ||
                    m_redis_server.empty())
            {

            } else
            {
                _re = true;
            }
        }
    }
    return _re;
}
