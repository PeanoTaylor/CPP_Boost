#include <iostream>
#include <sw/redis++/redis++.h>
using std::cout;
using std::endl;
using namespace sw::redis;

int main()
{
    try{
        auto redis = Redis("tcp://127.0.0.1:6379");

        // set
        redis.set("hello","world");

        // get
        auto val = redis.get("hello");
        cout << *val << endl;
        // exist
        bool exist = redis.exists("hello");
        cout << exist << endl;
        // del
        redis.del("hello");

        // 再次 GET
        auto v2 = redis.get("hello");
        std::cout << "After del, hello: " << (v2 ? *v2 : "<nil>") << std::endl;

        // list
        std::vector<std::string> elems;
        redis.lrange("mylist",0,-1,std::back_inserter(elems));
        for(auto &e : elems){
            cout << e << endl;
        }
    }catch(const Error &err){
        cout << err.what() << endl;
    }
    return 0;
}

