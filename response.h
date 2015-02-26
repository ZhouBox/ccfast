#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include <json/json.h>
#include "typedefs.h"
///
/// \brief The Response class
/// 将返回值封装成固定格式的字符串
class Response
{
public:
    static Response* instance();
    ///
    /// \brief json
    /// \param code_ 表示码 200->OK 400->error
    /// \param message_
    /// \param data_ 回复的数据
    /// \return
    ///
    static const std::string& json(int code_, const std::string& message_, const KVList& data_ = KVList());
    static const int m_s_buffer_size = 1000;
private:
    Response();
};

#endif // RESPONSE_H
