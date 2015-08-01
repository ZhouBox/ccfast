#ifndef FCGIWORKER_H
#define FCGIWORKER_H

#include "fcgiprogram.h"
#include "fcgi_stdio.h"
#include <string.h>
#include "response.h"
#include "sendemail.h"
#include "util.h"


template <typename T>
///
/// \brief The FcgiWorker class,to be a ane face
/// T1 FcgiProgram subclass
///
class FcgiWorker
{
public:
    FcgiWorker();
    ~FcgiWorker() {}
    void run();
private:
    boost::shared_ptr<FcgiProgram> m_fcgi;
};

template <typename T>
FcgiWorker<T>::FcgiWorker()
{
    m_fcgi = boost::shared_ptr<FcgiProgram>(new T());
}


template <typename T>
///
/// \brief FcgiWorker<T1, T2>::run
/// anything do in run
///
void FcgiWorker<T>::run()
{
    do {
        try
        {
            m_fcgi->init();
        } catch(const std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
            std::string _message = ex.what();
            _message += "<br>hostname:";
            _message += get_hostname();
            SendEmail::send("Fcgi_init_error!", format_send_email(_message));
            break;
        }

        while (FCGI_Accept() >= 0)
        {
            try
            {
                m_fcgi->process();
            } catch(const std::exception& ex1)
            {
                //print to log
                std::cerr << ex1.what() << std::endl;
                std::string _message = ex1.what();
                _message += "<br>hostname:";
                _message += get_hostname();
                SendEmail::send("Fcgi_runtime_error!", format_send_email(_message));
                FCGI_puts("Content-type:application/json; charset=UTF-8\r\n\r\n");
                FCGI_puts(Response::json(CODE_SYSERR, ex1.what(), KVList()).c_str());
                break;
            }
        }
        m_fcgi->end();

    }while(true);
}

#endif // FCGIWORKER_H
