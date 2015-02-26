#ifndef SENDEMAIL_H
#define SENDEMAIL_H

#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string.h>

///
/// \brief g_str_sendemailpy
///sendmail脚本在系统中的位置
const char* g_str_sendemailpy = "/etc/ccfast/sendmail.py";

///
/// \brief The SendEmail class
/// 使用system系统调用运行一个python脚本来发送邮件来上报一些消息
///
class SendEmail
{
public:
    ///
    /// \brief send
    /// \param title_ 邮件标题
    /// \param message_ 邮件内容
    /// \return
    ///
    static int send(const std::string& title_, const std::string& message_)
    {
        std::stringstream _ss;
        _ss << "python " << g_str_sendemailpy << " '" << title_ << "' '" << message_ << "'";
        std::string _cmd(_ss.str());
        const char* _cstrcmd = _cmd.c_str();
        return system(_cstrcmd);
    }
};

#endif // SENDEMAIL_H
