#include<iostream>
using namespace std;
bool canPlace(int a[][10],int i,int j,int n)
{
    int x,y;
    for(x=i;x>=0;x--)
        if(a[x][j]==1)
            return false;
    for(y=j;y>=0;y--)
        if(a[i][y]==1)
            return false;
    
    x=i;y=j;
    while(x>=0&&y>=0)
    {
        if(a[x][y]==1)
            return false;
        x--;
        y--;
    }
    x=i;y=j;
    while(x>=0&&y<n)
    {
        if(a[x][y]==1)
            return false;
        x--;
        y++;
    }
    return true;
}


bool nQueen(int a[][12],int i,int n)
{
    if(i==n)
    {
        for(int p=0;p<n;p++)
        {
            for(int q=0;q<n;q++)
            {
                cout<<a[p][q]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        return false;
    }

    for(int s=0;s<n;s++)
    {
        if(canPlace(a,i,s,n))
        {
            a[i][s]=1;
            bool canSolve=nQueen(a,i+1,n);
            if(canSolve)
                return true;
            a[i][s]=0; 
        }
    }
    return false;
}
int main()
{
    int n;
    cin>>n;
    int a[12][12]={0};
    bool ans=nQueen(a,0,0);
}