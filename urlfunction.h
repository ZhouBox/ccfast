///
///
///
/// 一个url对应一个function,保存与具体的业务相关的代码
///
#ifndef URLFUNCTION_H
#define URLFUNCTION_H
#include <string>
#include <fcgi_stdio.h>
#include "systemresource.h"
#include "analyticparameter.h"
#include "parse.h"


//METHOD只是一个提示作用,其不能限制这个功能的的范围
#define URL(LOCATION, METHOD)

template <typename T>
ParameterAnalytic<T>* get_parameter_analytic();
template <typename T>
Parse<T>* get_parse();

URL("/love", "GET")
void love(const std::string& data_);






#endif // URLFUNCTION_H
