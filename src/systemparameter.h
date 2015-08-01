#ifndef SYSTEMPARAMETER_H
#define SYSTEMPARAMETER_H

#include <json/json.h>
#include <fstream>

///
/// \brief The SystemParameter class
/// 从配置文件加载配置项
class SystemParameter
{
public:
    static SystemParameter* instance();
    ///
    /// \brief load 加载函数
    /// \return false error true ok
    /// throw exception
    bool load();
    std::string m_mysql_server;
    int m_mysql_port;
    std::string m_mysql_db;
    std::string m_mysql_user;
    std::string m_mysql_pwd;
    std::string m_redis_server;
    int m_redis_port;
    std::string m_redis_pwd;
private:
    SystemParameter();
};

#endif // SYSTEMPARAMETER_H
