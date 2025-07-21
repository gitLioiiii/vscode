#include<iostream>
using namespace std;
#define M 20000
int a[M][M];

int main()
{
    a[1][1]=1;
    int num=1;
    int N;
    cin>>N;
    for(int i=2;i<=M;i++)
        for(int j=1;j<=i;j++){
            a[i][j]=a[i-1][j-1]+a[i-1][j];
            num++;
            if(a[i][j]==N)
            {
                cout<<num<<endl;
                
            }
        }
        system("pause");
                return 0;
}
