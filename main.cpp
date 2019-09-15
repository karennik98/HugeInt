#include <iostream>
#include "./include/huge_int.h"

int main()
{
    try 
    {
        HugeInt num1("100000000000000000000000000000");
        HugeInt num2("-564897236497852369754896321455");
        HugeInt num3("1005856646646464646464646000");
        HugeInt num4("-1004464646464646462232323000");
        std::cout<<"num1: "<<num1<<std::endl;
        std::cout<<"num2: "<<num2<<std::endl;
        std::cout<<"num3: "<<num3<<std::endl;
        std::cout<<"num4: "<<num4<<std::endl;
        std::cout<<std::endl;

        std::cout<<"num1 - num2 = ";
        std::cout<<num1 - num2<<std::endl;

        std::cout<<"num1 + num2 = ";
        std::cout<<num1 + num2<<std::endl;

        std::cout<<"num1 * num2 = ";
        std::cout<<num1 * num2<<std::endl;

        std::cout<<"num1 / num2 = ";
        std::cout<<num1 / num2<<std::endl;

        std::cout<<"num1 + num3 = ";
        std::cout<<num1 + num3<<std::endl;

        std::cout<<"num1 - num3 = ";
        std::cout<<num1 - num3<<std::endl;

        std::cout<<"num1 * num3 = ";
        std::cout<<num1 * num3<<std::endl;

        // std::cout<<"num1 / num3 = ";
        // std::cout<<num1 / num3<<std::endl;

        std::cout<<"num2 + num4 = ";
        std::cout<<num2 + num4<<std::endl;

        std::cout<<"num2 - num4 = ";
        std::cout<<num2 - num4<<std::endl;

        std::cout<<"num2 * num4 = ";
        std::cout<<num2 * num4<<std::endl;

        // std::cout<<"num2 / num4 = ";
        // std::cout<<num2 / num4<<std::endl;
    }
    catch(Exception& ob)
    {
        std::cout<<ob.what()<<std::endl;
    }

    return 0;
}