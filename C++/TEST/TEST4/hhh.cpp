#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<int> k{1,2,3,4,5,6,7,8,9,10};
    vector<int> *p;
    p=&k;
    for (int  i = 0; i < p->size(); i++)
    {
        cout<<p->at(i)<<" ";
    }
    cout<<endl;
    //p->at(1)=100;  //通过指针访问vector中的元素
    system("pause");
    return 0;
}