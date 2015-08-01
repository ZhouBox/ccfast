/**
 * @file xxx
 * @brief Declaration file of class xxx.
 *
 * This file includes the declaration of class xxx, and
 * the definitions of the macros, struct, enum and so on.
 *
 * @attention used for C++ only.
 */

#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

 #ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include <list>
#include <string>
 #include "sessionmanagerimplpolicy.h"
 #include "util.h"
 #include "tpl/md5/md5.h"


template <typename T>
class SessionManager
{
public:
    SessionManager() : m_currentSessionId("")
    {

    }
    bool had() 
    {
        return m_sessionsManager.had(m_currentSessionId);
    }
    std::string get(const std::string& keyval)
    {
        return m_sessionsManager.get(m_currentSessionId, keyval);
    }
    const std::string& getCurrentSessionId() const
    {
        return m_currentSessionId;
    }
    void flushSessionId()
    {
        m_currentSessionId = GetSessionId();
    }
    bool set(const std::string& keyval, const std::string& value)
    {
        return m_sessionsManager.set(m_currentSessionId, keyval, value);
    }
    bool deleteKey(const std::string& keyVal)
    {
        return m_sessionsManager.deleteKey(keyVal);
    }
    bool deleteSession()
    {
        return m_sessionsManager.deleteSession(m_currentSessionId);
    }
    int ttl()
    {
        return m_sessionsManager.ttl(m_currentSessionId);
    }

    void getAll(std::vector<std::pair<std::string, std::string> >& vec)
    {
        m_sessionsManager.getAll(m_currentSessionId, vec);
    }
    std::string createSessionId()
    {
        std::string re = CurrentTimeStamp() + GetRemoteAddr();
        m_currentSessionId = md5sum(re.c_str(), re.size());
        return re;
    }
private:
    SessionManagerImplPolicy<T> m_sessionsManager;
    std::string m_currentSessionId;
};

#endif // SESSIONMANAGER_H
