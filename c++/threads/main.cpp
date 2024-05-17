/* To build - g++ main.cpp */

#include <iostream>
#include <thread>

void fnc(int i, std::string s)
{ 
    std::cout<<"Hello from thread!"<<std::endl;
    std::cout<<"Number: "<<i<<std::endl;
    std::cout<<s<<std::endl;
}

int main()
{
    std::thread thread_obj(fnc, 5, "Hello"); /* Tworzenie wątku */
    
    /* How can I update to C++ 20?!?!?!??! */
    //std::jthread thread_obj2(fnc, 4, "Hello"); /* Tworzenie wątku */

    thread_obj.join(); /* Waits for thread_obj to finish */

    return 0;
}