#include<bits/stdc++.h>
using namespace std;

bool canPlace(int a[][20],int n,int x,int y,int num)
{
    int i;
    if(a[x][y]!=0)
        return false;

    for(i=0;i<n;i++)
    {
        if(a[i][y]==num)
            return false;
        if(a[x][i]==num)
            return false;
    }

    int block=sqrt(n);
    int rowBeg=(x/block)*block;
    int colBeg=(y/block)*block;
    for(i=rowBeg;i<rowBeg+block;i++)
        for(int j=colBeg;j<colBeg+block;j++)
            if(a[i][j]==num)
                return false;

    return true;
}
bool sudoku(int a[][20],int n,int x,int y)
{
    if(x==n)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;

        return true;
    }

    if(y==n)
        return sudoku(a,n,x+1,0);

    for(int i=1;i<=n;i++)
    {
        if(canPlace(a,n,x,y,i))
        {
            a[x][y]=i;
            bool canSolve = sudoku(a,n,x,y+1);
            if(canSolve)
                return true;
            a[x][y]=0;
        }
    }
    return false;
}

int main()
{
    int n;
    cin>>n;
    int a[20][20],i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cin>>a[i][j];
    bool res=sudoku(a,n,0,0);
    cout<<res;
}
