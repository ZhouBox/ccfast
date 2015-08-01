#include "stringbuilder.h"


StringBuilder& operator<< (StringBuilder& ss, const std::string& str)
{
    ss.m_ss << str;
    return ss;
}

StringBuilder::StringBuilder()
{

}

StringBuilder::~StringBuilder()
{

}

void StringBuilder::append(const std::string& str)
{
    m_ss << str;
}

std::string StringBuilder::toString()
{
    return m_ss.str();
}

void StringBuilder::clear()
{
    m_ss.str("");
}

