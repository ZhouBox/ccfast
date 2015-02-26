#include <iostream>
#include "fcgiworker.h"
#include "util.h"
#include "parse.h"
#include "urlroute.h"
#include "ccfastprogram.h"
#include "urlfunction.h"
#include "response.h"
#include "systemparameter.h"

int main()
{
    SystemParameter* _sp = SystemParameter::instance();

    do{
        try
        {
            if (!_sp->load())
            {
                SendEmail::send("Fcgi_load_conf_error!", "load mysql redis conf error!");
                break;
            }
        }catch(const std::exception& ex)
        {
            //解析参数的参数的过程中,可以会抛出异常
            std::string _message = ex.what();
            std::cout << ex.what();
            _message += "<br>hostname:";
            _message += get_hostname();
            SendEmail::send("Fcgi_load_conf_error!", format_send_email(_message));
            break;
        }

        UrlRoute* _p = UrlRoute::instance();
        _p->set_project("/ccfast");
        _p->register_url("/love.do", love);
        FcgiWorker<CcFastProgram> _fcgi;
        _fcgi.run();

    }while(0);

    return 0;
}

