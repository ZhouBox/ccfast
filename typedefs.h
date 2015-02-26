#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <list>
#include <string>
#include <vector>
#include <boost/functional/hash.hpp>


///
/// some typedef type
///
///
///
///
///

typedef std::list<std::string> StringList;

typedef std::pair<std::string, std::string> _2string;

typedef std::vector<_2string> _2stringVector;

typedef boost::hash<std::string> string_hash;

typedef std::list<_2string> KVList;


//返回给客户端的一些code以及code的message
#define CODE_ERROR 400
#define MESSAGE_ERROR "THE SERVER DOES NOT UNDERSTAND THE REQUEST OF GRAMMAR!"
#define CODE_OK 200
#define MESSAGE_OK "OK"
#define CODE_SYSERR 401
#define MESSAGE_SYSERR "SYSTEM ERROR!"


//post操作读取表单中的数据的缓存大小
#define CONTENT_LEN (1024 * 2)




#endif // TYPEDEFS_H
