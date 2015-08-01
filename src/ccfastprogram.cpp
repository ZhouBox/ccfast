#include "ccfastprogram.h"
#include "systemresource.h"
#include "util.h"
#include "urlroute.h"
#include "fcgi_stdio.h"
#include "response.h"
#include "systemparameter.h"


CcFastProgram::CcFastProgram()
{
}

void CcFastProgram::init()
{
    SystemResource* _p = SystemResource::instance();
    const SystemParameter* _sp = SystemParameter::instance();
    try
    {
        _p->mysql_connection = boost::shared_ptr<mysqlpp::Connection>(new mysqlpp::Connection(true));
        _p->redis_client = get_redis_client();
        //open database
        //
        //
        _p->mysql_connection->connect(_sp->m_mysql_db.c_str(), _sp->m_mysql_server.c_str(),
                                      _sp->m_mysql_user.c_str(), _sp->m_mysql_pwd.c_str(), _sp->m_mysql_port);
        _p->mysql_query = boost::shared_ptr<mysqlpp::Query>(new mysqlpp::Query(_p->mysql_connection.get(), true));
    } catch (const redis::redis_error &redis_error)
    {
        throw redis_error;
    }
    catch (const mysqlpp::Exception& mysql_error)
    {
        throw mysql_error;
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

void CcFastProgram::process()
{
    const char *_script_name = getenv("SCRIPT_NAME");
    const char *_request_method = getenv("REQUEST_METHOD");
    if (_script_name == NULL || _request_method == NULL)
    {
        FCGI_puts("Content-type:application/json; charset=UTF-8\r\n\r\n");
        FCGI_puts(Response::json(CODE_ERROR, MESSAGE_ERROR).c_str());
    } 
    else {
        const UrlRoute* _p = UrlRoute::instance();
        UrlRoute::dourlfunction f = _p->get_func(m_string_hash(_script_name));
        if (!f)//无效的路由
        {
            FCGI_puts("Content-type:application/json; charset=UTF-8\r\n\r\n");
            FCGI_puts(Response::json(CODE_ERROR, MESSAGE_ERROR, KVList()).c_str());
        }
        else {
            do
            {
                if (strcmp(_request_method, "GET") == 0)
                {
                    const char *_query_string = getenv("QUERY_STRING");
                    if (_query_string)
                    {
                        f(_query_string);
                    } else {
                        FCGI_puts("Content-type:application/json; charset=UTF-8\r\n\r\n");
                        FCGI_puts(Response::json(CODE_ERROR, MESSAGE_ERROR).c_str());
                    }
                    break;
                }
                if (strcmp(_request_method, "POST") == 0)
                {
                    const char* _content = get_content();
                    if (_content)
                    {
                        f(_content);
                    } else
                    {
                        FCGI_puts("Content-type:application/json; charset=UTF-8\r\n\r\n");
                        FCGI_puts(Response::json(CODE_ERROR, MESSAGE_ERROR, KVList()).c_str());
                    }

                }
            } while(0);
        }
    }
}



void CcFastProgram::end()
{

}
