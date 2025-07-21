#include<iostream>
// using namespace std;

void swap(int *x,int *y){
    int temp=*x;
    *x=*y;
    *y=temp;
}
int main(){
    int a,b;
    std::cin>>a>>b;
    std::cout<<"Before swapping"<<std::endl;
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"b = "<<b<<std::endl;
    swap(&a,&b);
    std::cout<<"After swapping"<<std::endl;
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"b = "<<b<<std::endl;
    system("pause");
    return 0;
}