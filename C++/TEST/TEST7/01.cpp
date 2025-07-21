#include<iostream>

void test01(){
    std::cout<<"The world is very beautiful!"<<std::endl;
}

void test02(int a , int b){
    std::cout<<"The sum of a and b is "<<a+b<<std::endl;
}

int test03(int a , int b){
    return a+b;
}

int test04(){
    return 10000;
}

int main(){
    test01();
    test02(10 , 20);
    std::cout<<test03(20 , 20)<<std::endl;
    int num = test04();
    std::cout<<"num等于"<<num<<std::endl;
    system("pause");
    return 0;
}
