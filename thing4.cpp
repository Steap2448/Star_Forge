#include <iostream>
#include <cstdlib>
using namespace std;
#define N 48
#define M 96

class Object
{
	public:
	double radius;
	double mass;
	double x;
	double y;
	double acseleration;
	Object(double a,double b,double c,double d)
	{
		radius=a;
		mass=b;
		x=c;
		y=d;
	}
};

int ObjectCreate(Object p1,char field[N][M])
	{
		int i,j;
		int c1=(int)p1.y,c2=(int)p1.x,r=(int)p1.radius;
		field[c1][c2]='*';
		for (i=0;i<=r;i++)
		{
			for (j=0;j<=i;j++)
			{
				field[c1-r+i][c2+j]='*';
				field[c1-r+i][c2-j]='*';
			}
		}
		for (i=0;i<=r;i++)
		{
			for (j=0;j<=i;j++)
			{
				field[c1+r-i][c2+j]='*';
				field[c1+r-i][c2-j]='*';
			}
		}
		return 0;
	}
	
	int ObjectCreate2(Object p1,char field[N][M])
	{
		int i,j,l,o,z;
		int c1=(int)p1.y,c2=(int)p1.x,r=(int)p1.radius;
		field[c1][c2]='*';
		if(r>8||r<16)
		{
			l=3;
			z=1;
		}
		if(r<9)
		{
			l=2;
		}
		if(r<4)
		{
			l=1;
		}
		if(r-l>=3)
		{
			o=1;
		}
		for (i=0;i<=r-l;i++)
		{
			for (j=i+l;j>=0;j--)
			{
				field[c1-r+i][c2+j*2]='*';
				field[c1-r+i][c2-j*2]='*';
			}
		}
		for (i=0;i<=r-l;i++)
		{
			for (j=i+l;j>=0;j--)
			{
				field[c1+r-i][c2+j*2]='*';
				field[c1+r-i][c2-j*2]='*';
			}
		}
		for(i=0;i<l;i++)
		{
			for (j=r;j>=0;j--)
			{
				field[c1+i][c2+j*2]='*';
				field[c1+i][c2-j*2]='*';
				field[c1-i][c2+j*2]='*';
				field[c1-i][c2-j*2]='*';
			}
		}
		if(o==1)
		{
			for(i=0;i<r-5;i++){	
				field[c1+l+2+i][c2+(r-1-i)*2]='*';
				field[c1-l-2-i][c2+(r-1-i)*2]='*';
				field[c1+l+2+i][c2-(r-1-i)*2]='*';
				field[c1-l-2-i][c2-(r-1-i)*2]='*';
				field[c1+(r-1-i)][c2+(l+2-i)*2]='*';
				field[c1-(r-1-i)][c2+(l+2-i)*2]='*';
				field[c1+(r-1-i)][c2-(l+2-i)*2]='*';
				field[c1-(r-1-i)][c2-(l+2-i)*2]='*';
			}
		}
		return 0;
	}
int main()
{
	int i,j;
	double a,b,c,d;
	char field[N][M];
	for (i=1;i<N-1;i++)
	{
		field[i][0]='|';
		field[i][M-1]='|';
		for (j=1;j<M-1;j++)
		field[i][j]=' ';
	}
		for (j=1;j<M-1;j++)
	{
		field[0][j]='-';
		field[N-1][j]='-';
	}
	field[0][0]='+';
	field[0][M-1]='+';
	field[N-1][0]='+';
	field[N-1][M-1]='+';
	cin>>a>>b>>c>>d;
	Object p1(a,b,c,d);
	//field[(int)p1.y][(int)p1.x]='*';
	ObjectCreate2(p1,field);
	for (i=0;i<N;i++)
	{
		for (j=0;j<M;j++)
		{
			cout<<field[i][j];	
		}
		cout<<"\n";
	}
	return 0;
}
