/*
This program produces hashes for small text. It is based on SHA1
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void print(bool h[32],int len)
{
int i;
for(i=0;i<len;i++)
        printf("%d",h[i]);
}



bool *function1(bool *b,bool *c,bool *d, bool*f)
{
int i;
static bool k[32]={0,1,0,1,1,0,1,0,1,0,0,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1};
for(i=0;i<32;i++)
	f[i]=((b[i] and c[i]) or (not(b[i]) and d[i]));

return k;	
}

bool *function2(bool *b,bool *c,bool *d, bool*f)
{
int i;
static bool k[32]={0,1,1,0,1,1,1,0,1,1,0,1,1,0,0,1,1,1,1,0,1,0,1,1,1,0,1,0,0,0,0,1};
for(i-0;i<32;i++)
	f[i]=(b[i] xor c[i]) xor d[i];
return k;
}


bool *function3(bool *b,bool *c,bool *d, bool*f)
{
int i;
static bool k[32]={1,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,1,1,1,0,0};

for(i-0;i<32;i++)
        f[i]=(b[i] and c[i]) or (b[i] and d[i]) or (c[i] and d[i]);
return k;
}


bool *function4(bool *b,bool *c,bool *d, bool*f)
{
int i;
static bool k[32]={1,1,0,0,1,0,1,0,0,1,1,0,0,0,1,0,1,1,0,0,0,0,0,1,1,1,0,1,0,1,1,0};
for(i-0;i<32;i++)
        f[i]=(b[i] xor c[i]) xor d[i];
return k;
}


void func_xor(bool *a,bool *b,bool* c)
{
int i;
for(i=0;i<32;i++)
	c[i]=a[i] xor b[i];
}


void twoadd(bool a[32], bool b[32], bool *c)
{
int i;
int carry=0,temp;

for(i=31;i>=0;i--)
	{
	temp=a[i]+b[i]+carry;
	carry=temp/2;
	c[i]=temp%2;
	}

}

void add(bool *a, bool *b, bool *c, bool *d, bool *e, bool *ans)
{
bool temp[32];

twoadd(a,b,temp);
twoadd(c,temp,ans);
twoadd(d,ans,temp);
twoadd(e,temp,ans);

}


void boolean(bool *input,int x,int i,int j)
{
int count=j;

while(x>0)
	{
	input[count]=x%2;
	count--;
	x=x/2;	
	}

while(count>=i)
	{
	input[count]=0;
	count--;
	}
}

void copy(bool *a, bool *b)
{
int i;
for(i=0;i<32;i++)
	a[i]=b[i];	
}


void convert(bool *h)
{
int i,temp;
for(i=8;i>0;i--)
	{
	temp=h[4*i-1]*8 + h[4*i-2]*4 + h[4*i-3]*2 + h[4*i-4];
	if(temp>9)
		temp+=55;

	else
		temp+=48;
	printf("%c",temp); 
	}
}

int main()
{
bool h0[32] = {0,1,1,0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,1};
bool h1[32] = {1,1,1,0,1,1,1,1,1,1,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0,1};
bool h2[32] = {1,0,0,1,1,0,0,0,1,0,1,1,1,0,1,0,1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,0};
bool h3[32] = {0,0,0,1,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,0,0,1,1,1,0,1,1,0};
bool h4[32] = {1,1,0,0,0,0,1,1,1,1,0,1,0,0,1,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0};
char str[100];
bool *input,*array;
int i,x,j,len=32;

scanf("%[^\n]s",str);
int length=8*strlen(str);
input = (bool *)malloc(sizeof(bool)*(length+1));

for(i=0;i<strlen(str);i++)
	{
	x=(int)str[i];
	boolean(input,x,i*8,7+i*8);		
	}

input[length]=1;
x=1;
while(x*512-64< length+1)
	{
	x++;
	}

array = (bool *)malloc(sizeof(bool)*(x*512 - (length+1)));
int size = x*512;
for(i=0;i<size;i++)
	{
	if(i<=length)
		array[i]=input[i];

	else
		array[i]=0;
	}
free(input);

boolean(array,length,size-64,size-1);

bool word[80][32]={0};
for(i=0;i<80;i++)
	{
	if(i<16)
		{
		for(j=0;j<32;j++)
			word[i][j]=array[i*32+j];
		}
	}

bool temp1[32],temp2[32];

for(i=16;i<80;i++)
	{
	func_xor(word[i-3],word[i-8],temp1);
	func_xor(temp1,word[i-14],temp2);
	func_xor(temp2,word[i-16],temp1);
	for(j=1;j<32;j++)
		word[i][j-1]=temp1[j];
	word[i][31]=temp1[0];	
	}	

bool a[32],b[32],c[32],d[32],e[32],f[32],temp[32];

for(i=0;i<32;i++)
	{
	a[i]=h0[i];
	b[i]=h1[i];
	c[i]=h2[i];
	d[i]=h3[i];
	e[i]=h4[i];
	}


bool *k;
for(i=0;i<80;i++)
	{
	if(i<20)
		k = function1(b,c,d,f);

	else if(i<40)
		k = function2(b,c,d,f);

	else if(i<60)
		k = function3(b,c,d,f);

	else
		k = function4(b,c,d,f);

	for(j=5;j<32;j++)
		temp1[j-5]=a[j];

	for(j=0;j<5;j++)
		temp1[27+j]=a[j];	

	add(temp1,f,e,k,word[i],temp);
	copy(e,d);
	copy(d,c);

	for(j=0;j<30;j++)
		temp2[j+2]=b[j];
	temp2[0]=b[30];
	temp2[1]=b[31];

	copy(c,temp2);
	copy(b,a);
	copy(a,temp);
	}

twoadd(h0,a,h0);
twoadd(h1,b,h1);
twoadd(h2,c,h2);
twoadd(h3,d,h3);
twoadd(h4,e,h4);
convert(h0);
convert(h1);
convert(h2);
convert(h3);
convert(h4);
printf("\n");
}
