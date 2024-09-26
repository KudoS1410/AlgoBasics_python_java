#include<iostream>
using namespace std;
void solveMaze(int a[][10],int s[][10],int x,int y,int n)
{
    if(x==n-1&&y==n-1)
    {
        s[x][y]=1;
        for(int p=0;p<n;p++)
        {
            for(int q=0;q<n;q++)
            {
                cout<<s[p][q]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        return;
    }
    if(x<0||y<0||x>n-1||y>n-1||a[x][y]==0||s[x][y]==1)
        return;

    s[x][y]=1;
    solveMaze(a,s,x,y+1,n);
    solveMaze(a,s,x+1,y,n);
    s[x][y]=0;
}
int main()
{
    int n;
    cin>>n;
    int a[10][10];

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];

    int s[10][10]={0};
    
    solveMaze(a,s,0,0,n);
}