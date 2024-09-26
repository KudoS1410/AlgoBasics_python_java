#include<iostream>
using namespace std;
long l=1000000007;
int main()
{
    int t;
    long a,b,c,sum,ans,i,d,val,p;
    cin>>t;
    while(t--)
    {
        sum=0;ans=0;
        cin>>a>>b>>c;
        a--;c--;
        for(p=1;p<=b;p++)
        {
            val=p*p;
        
            for(i=1;i<=p&&i<=c;i++)
            {
                d=val/i;
                if(a>d)
                    sum+=a-d;
            }
            for(i=1;i<=p&&i<=a;i++)
            {
                d=val/i;
                if(c>d)
                    sum+=c-d;
            }
            
            sum=sum%l;
            if(a>p&&c>p)
            {
                ans=(((a-p)%l)*((c-p)%l))%l;
                sum = (sum+ans)%l;
            }
        }
        cout<<sum<<endl;
    }
}

/*

#include<iostream>
using namespace std;
int ans(int* a,int n,int i)
{
	if(x==n)
}
int main() {
	int n,i,t;
	int a[45];
	cin>>t;
	while(t--)
	{
		cin>>n;
		
	}


	
	for(i=0;i<n;i++)
		cin>>a[i];
	cout<<game(a,0,n-1);
	return 0;
}
*/

/*



