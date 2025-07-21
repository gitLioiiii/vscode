#include<iostream>
#include<fstream>

using namespace std;
int main()
{
    ifstream inf;
    inf.open("C:\\Users\\LIXIN\\Desktop\\123.txt");
    
    if(!inf)
    {
        cout<<"文件打开失败"<<endl;
        return 0;
    }
    char x;
   while(inf>>x)
   {
       cout<<x;
   }
   cout<<endl;
   inf.close();
   system("pause");
    return 0;
}