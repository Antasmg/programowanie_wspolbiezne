/* To build - g++ main.cpp */

#include <iostream>
#include <thread>

using namespace std::literals;

class PW{
    public:
    void operator()(int i, std::string s)
    {
        std::cout<<"Hello from thread!"<<std::endl;
        std::this_thread::sleep_for(2s); /* Do tego potrzebne jest std::literals */
        std::cout<<"Number: "<<i<<std::endl;
        std::cout<<s<<std::endl;
    }
};

int main()
{
    PW o;
    std::thread thread_obj(o, 5, "Hello"); /* Tworzenie wątku */
    std::thread thread_obj2(o, 3, "Hej"); /* Tworzenie wątku */
    std::thread thread_obj_lambda([]{std::cout<<"Hello from lambda"<<std::endl;}); /* Tworzenie wątku typu lambda */
    thread_obj.join(); /* Waits for thread_obj to finish */
    thread_obj2.join(); /* Waits for thread_obj2 to finish */
    thread_obj_lambda.join(); /* Waits for thread_obj_lambda to finish */

    return 0;
}