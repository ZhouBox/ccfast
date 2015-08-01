#ifndef SESSIONMANAGERIMPLPOLICY_H
#define SESSIONMANAGERIMPLPOLICY_H


#include <string>
#include <tuple>
#include <vector>

template <typename T>
class SessionManagerImplPolicy
{
public:
    SessionManagerImplPolicy() : m_t(NULL)
    {
        m_t = new T();
    }

    ~SessionManagerImplPolicy()
    {
        delete m_t;
    }

    bool had(const std::string& sessionId)
    {
        return m_t->had(sessionId);
    }

    std::tuple<std::string, bool> get(const std::string& sessionId, const std::string& keyval)
    {
        return m_t->get(sessionId, keyval);
    }

    bool set(const std::string& sessionId, const std::string &keyval, const std::string& value)
    {
        return m_t->set(sessionId, keyval, value);
    }

    bool deleteKey(const std::string& sessionId, const std::string& keyval)
    {
        return m_t->deleteKey(sessionId, keyval);
    }

    bool deleteSession(const std::string& sessionId)
    {
        return m_t->deleteSession(sessionId);
    }

    void getAll(const std::string& sessionId, std::vector<std::pair<std::string, std::string> > &vec)
    {
        m_t->getAll(sessionId, vec);
    }

private:
    T *m_t;

};










#endif //SESSIONMANAGERIMPLPOLICY_H