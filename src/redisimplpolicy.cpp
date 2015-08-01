#include "redisimplpolicy.h"
#include "systemresource.h"

const int TTL = 60 * 21;

RedisImplPolicy::RedisImplPolicy()
{

}

RedisImplPolicy::~RedisImplPolicy()
{

}

bool RedisImplPolicy::had(const std::string& sessionId)
{
    bool re = false;
    SystemResource * systemresource = SystemResource::instance();
    re = systemresource->redis_client->exists(sessionId);
    if (re) {
        systemresource->redis_client->expire(sessionId, TTL);
    }
    return re;
}

std::tuple<std::string, bool> RedisImplPolicy::get(const std::string &sessionId, const std::string &keyval)
{
    std::tuple<std::string, bool> re = std::make_tuple(std::string(), false);
    SystemResource * systemresource = SystemResource::instance();
    std::string val = systemresource->redis_client->hget(sessionId, keyval);
    re = std::make_tuple(val, true);
    systemresource->redis_client->expire(sessionId, TTL);
    return re;
    
}

bool RedisImplPolicy::set(const std::string &sessionId, const std::string &keyval, const std::string &value)
{
    bool re = false;
    SystemResource * systemresource = SystemResource::instance();
    re = systemresource->redis_client->hset(sessionId, keyval, value);
    systemresource->redis_client->expire(sessionId, TTL);
    return re;
}

bool RedisImplPolicy::deleteKey(const std::string &sessionId, const std::string &keyval)
{
    bool re = false;
    SystemResource * systemresource = SystemResource::instance();
    re = systemresource->redis_client->hdel(sessionId, keyval);
    systemresource->redis_client->expire(sessionId, TTL);
    return re;
}

bool RedisImplPolicy::deleteSession(const std::string& sessionId)
{
    bool re = false;
    SystemResource * systemresource = SystemResource::instance();
    re = systemresource->redis_client->del(sessionId);
    return re;
}

void RedisImplPolicy::getAll(const std::string& sessionId, std::vector<std::pair<std::string, std::string> >& vec) 
{
    SystemResource * systemresource = SystemResource::instance();
    systemresource->redis_client->hgetall(sessionId, vec);
    systemresource->redis_client->expire(sessionId, TTL);
}

int RedisImplPolicy::ttl(const std::string& sessionId)
{
    int time = -1;
    SystemResource * systemresource = SystemResource::instance();
    time = systemresource->redis_client->ttl(sessionId);
    return time;
}
