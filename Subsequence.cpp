#include<iostream>
using namespace std;
long l=1000000007;
int* multiply(int* A, int* B, int m, int n) 
{ 
   int *prod = new int[m+n-1];
    for (int i = 0; i<m+n-1; i++) 
        prod[i] = 0;  
    for (int i=0; i<m; i++) 
    { 
        for (int j=0; j<n; j++) 
            prod[i+j] += A[i]*B[j]; 
    }     
  
    return prod; 
} 

int main()
{
    int f[8001],mul[8001][2],x,n,i,r,sum,k;
    for(i=0;i<=8000;i++)
        f[i]=0;
    cin>>n>>k;
    for(i=0;i<n;i++)
    {
        cin>>x;
        f[x]++;
    }
    r=0;
    for(i=0;i<=8000;i++)
    {
        if(f[i])
        {
            mul[r][0]=1;
            mul[r++][1]=f[i];
        }
    }
        
    int* prod=multiply(mul[0], mul[1], 2, 2);
    for(i=2;i<r;i++)
    {
        prod=multiply(mul[i], prod, 2, i+1); 
    }
    sum=0;
    for(i=0;i<=k;i++)
    {
        sum+=prod[i]%l;
    }

    cout<<sum%l<<endl;

    return 0;
}