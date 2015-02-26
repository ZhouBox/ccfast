#ifndef URLROUTE_H
#define URLROUTE_H
#include <string>
#include <hash_map>
#include "typedefs.h"

///
/// \brief The UrlRoute class
/// url route
/// use hash to find url
/// 使用hash值来表示唯一的URL
/// 简单的路由,将url对应到具体的逻辑代码
class UrlRoute
{
public:
    static UrlRoute* instance()
    {
        static UrlRoute _s_urlroute;
        return &_s_urlroute;
    }

    typedef void (*dourlfunction)(const std::string& data_);
    typedef __gnu_cxx::hash_map<size_t, dourlfunction> type_value;
    dourlfunction get_func(size_t id_) const
    {
        type_value::const_iterator _ite = m_urlmapfunc.find(id_);
        if (_ite != m_urlmapfunc.end())
        {
            return (*_ite).second;
        }
        return NULL;
    }
    void register_url(const std::string& url_, dourlfunction fun_)
    {
        m_urlmapfunc[m_stringhash(m_strproject + url_)] = fun_;
    }
    ///
    /// \brief set_project 设置项目名,与集体的前端服务器配置(nginx)有关
    /// \param project_
    ///
    void set_project(const std::string project_)
    {
        m_strproject = project_;
    }

    ///
    /// \brief get_project
    /// \return
    ///
    const std::string& get_project() const
    {
        return m_strproject;
    }

private:
    UrlRoute(){}
    __gnu_cxx::hash_map<size_t, dourlfunction> m_urlmapfunc;
    string_hash m_stringhash;
    std::string m_strproject;
};


#endif // URLROUTE_H
