#include <iostream>
#include "./include/huge_int.h"

int main()
{
    try 
    {
        HugeInt num1("50000");
        HugeInt num2("-10");
        HugeInt num3("100000000");
        HugeInt num4("-2");
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

        std::cout<<"num1 / num3 = ";
        std::cout<<num1 / num3<<std::endl;

        std::cout<<"num2 + num4 = ";
        std::cout<<num2 + num4<<std::endl;

        std::cout<<"num2 - num4 = ";
        std::cout<<num2 - num4<<std::endl;

        std::cout<<"num2 * num4 = ";
        std::cout<<num2 * num4<<std::endl;

        std::cout<<"num2 / num4 = ";
        std::cout<<num2 / num4<<std::endl;
    }
    catch(Exception& ob)
    {
        std::string str(ob.what());
        std::cout<<ob.what()<<std::endl;
    }

    return 0;
}