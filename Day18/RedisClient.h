#ifndef __REDIS_CLIENT_H__
#define __REDIS_CLIENT_H__
#include <hiredis/hiredis.h>
#include <string>
using std::string;
using std::cout;
using std::endl;

class RedisClient{
public:
    RedisClient(const string &host = "127.0.0.1",int port = 6379);
    ~RedisClient();

    bool set(const string &key,const string &value);
    string get(const string &key);

private:
    RedisClient(const RedisClient&) = delete;
    RedisClient &operator=(const RedisClient&) = delete;
    redisContext* m_ctx;
};
#endif
