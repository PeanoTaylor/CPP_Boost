#include <iostream>
#include <hiredis/hiredis.h>
using std::cout;
using std::endl;

int main()
{
    redisContext *conn = redisConnect("127.0.0.1",6379);
    if(conn == NULL || conn->err){
        if(conn){
            printf("Connection error: %s\n", conn->errstr);
            redisFree(conn);
        }else {
            printf("Can't allocate redis context\n");
        }
    }
    cout << "connect success"<<endl;

    /* // 2.set */
    /* redisReply *reply = (redisReply *)redisCommand(conn,"SET %s %s","foo", "hello hiredis"); */
    /* printf("SET: %s\n", reply->str); */
    /* freeReplyObject(reply); */


    /* // 3. 发送 GET 命令 */
    /* reply = (redisReply*)redisCommand(conn, "GET %s", "foo"); */
    /* if (reply->type == REDIS_REPLY_STRING) */
    /*     printf("GET foo: %s\n", reply->str); */
    /* freeReplyObject(reply); */
    
    redisReply *reply = (redisReply *)redisCommand(conn,"LRANGE mylist 0 -1");
    if(reply->type == REDIS_REPLY_ARRAY){
        for(size_t i = 0; i < reply->elements; ++i){
            printf("%zu: %s\n", i, reply->element[i]->str);
        }
    }
    // 4
    redisFree(conn);
    return 0;
}

