#ifndef SYSTEMRESOURCE_H
#define SYSTEMRESOURCE_H

#include <redisclient.h>
#include <mysql++/mysql++.h>
///
/// \brief The SystemResource class
///一个系统资源集合
class SystemResource
{
public:
    static SystemResource* instance()
    {
        static SystemResource _s_system_resource;
        return &_s_system_resource;
    }

    boost::shared_ptr<redis::client> redis_client;
    boost::shared_ptr<mysqlpp::Connection> mysql_connection;
    boost::shared_ptr<mysqlpp::Query> mysql_query;
private:
    SystemResource(){}

};

#endif // SYSTEMRESOURCE_H
