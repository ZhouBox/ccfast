#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <sstream>
#include <string>

class StringBuilder
{
    friend StringBuilder& operator << (StringBuilder &ss, const std::string &str);
public:
    StringBuilder();
    ~StringBuilder();
    void append(const std::string &str);
    std::string toString();
    void clear();
private:
    std::stringstream m_ss;

};


#endif //STRINGBUILDER_H