///
///
///
/// 一个url对应一个function,保存与具体的业务相关的代码
///
#ifndef URLFUNCTION_H
#define URLFUNCTION_H
#include <string>
#include <fcgi_stdio.h>


//METHOD只是一个提示作用,其不能限制这个功能的的范围
#define URL(LOCATION, METHOD)


URL("/love.do", "GET")
void love(const std::string& data_);






#endif // URLFUNCTION_H
