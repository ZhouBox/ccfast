#ifndef REDISIMPLPOLICY_H
#define REDISIMPLPOLICY_H


#include <string>
#include <tuple>
#include <vector>

class RedisImplPolicy
{
  public:
    RedisImplPolicy();
    ~RedisImplPolicy();
    bool had(const std::string &sessionId);
    std::tuple<std::string, bool> get(const std::string &sessionId, const std::string &keyval);
    bool set(const std::string &sessionId, const std::string &keyval, const std::string &value);
    bool deleteKey(const std::string &sessionId, const std::string &keyval);
    bool deleteSession(const std::string& sessionId);
    void getAll(const std::string& sessionId, std::vector<std::pair<std::string, std::string> > &vec);
    int ttl(const std::string& sessionId);
};

#endif //REDISIMPLPOLICY_H