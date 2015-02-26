/*
 *
 *
 *some tool function
 *
 *
 *
*/

#ifndef UTIL_H
#define UTIL_H

#include "typedefs.h"
#include "redisclient.h"
#include <sstream>
#include <stdio.h>



boost::shared_ptr<redis::client> get_redis_client();

int string2int(const std::string& str_);

std::string int2string(int id_);

StringList& operator<<(StringList& slist_, const std::string& str_);

StringList split(const std::string& str_, char c_);

///
/// \brief format_send_email 将发送字符串中的'\''符号转换为'`',使其可以作为python脚本的参数
/// \param message_
/// \return
///
std::string &format_send_email(std::string &message_);

const char* get_hostname();

const char* get_content();




#endif // UTIL_H
