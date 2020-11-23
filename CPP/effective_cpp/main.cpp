#include <iostream>
#include <string>

//using namespace std;

class A
{
public:
    ~A()
    {
        std::cout<<"A Destructor"<<std::endl;
    }
};

class B:public A
{
    public:
    ~B()
    {
        std::cout<<"B Destructor"<<std::endl;
    }

};


int main(int argc,char** argv)
{
    A* a = new B;
    delete a;
    return 0;
}