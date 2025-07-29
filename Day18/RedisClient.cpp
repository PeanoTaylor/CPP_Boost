#include <iostream>
#include "RedisClient.h"

RedisClient::RedisClient(const string& host, int port)
    : m_ctx(nullptr){
        m_ctx = redisConnect(host.c_str(),port);
        if(m_ctx == NULL || m_ctx->err){
            if(m_ctx){
                printf("Connection error: %s\n", m_ctx->errstr);
                redisFree(m_ctx);
            }else {
                printf("Can't allocate redis context\n");
            }   
        }   
    }

RedisClient::~RedisClient(){
    if(m_ctx){
        redisFree(m_ctx);
        m_ctx = nullptr;
    }
}

bool RedisClient::set(const string &key, const string &value){
    if(!m_ctx)
        return false;
    redisReply *reply = (redisReply *)redisCommand(m_ctx,"SET %s %s",key.c_str(),value.c_str());
    if(!reply)
        return false;

    bool res = false;
    if(reply->type == REDIS_REPLY_STATUS && string(reply->str) == "OK"){
        res = true;
    }

    freeReplyObject(reply);
    return res;
}

string RedisClient::get(const string &key){
    if (!m_ctx) 
        return "";
    redisReply* reply = (redisReply*)redisCommand(m_ctx, "GET %s", key.c_str());
    if (!reply) 
        return "";

    string res = "";
    if (reply->type == REDIS_REPLY_STRING && reply->str) {
        res = reply->str;
    }
    freeReplyObject(reply);
    return res;
}

void test(){
    RedisClient client("127.0.0.1", 6379);

    // SET 测试
    if (client.set("name", "Alice")) {
        cout << "Set name=Alice OK!" << endl;
    } else {
        cout << "Set name=Alice failed!" << endl;
    }

    // GET 测试
    string value = client.get("name");
    if (!value.empty()) {
        cout << "Get name: " << value << endl;
    } else {
        cout << "Get name failed or key not found." << endl;
    }

}
int main()
{
    test();
    return 0;
}

