/*
This program takes encypted data and private key and decryptes it
*/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int p=61,q=53,n=3233;


long long int compute(int y,int q)
{
if(q==2)
	return y*y;

if(q==1)
	return y;

long long int x=compute(y,q/2);

if(q%2==0)
	return (x*x)%n;

else
	return (((x*x)%n)*(y))%n;
}


int main()
{
char file[100],newf[100];
int status,len,i,j,x,key,count=0,temp[10],size;;
printf("Enter the file to decrypt:");
scanf("%s",file);

FILE *fp,*newfile;
long lSize;
char *buffer;

for(i=0;i<strlen(file)-4;i++)
	{
	newf[i]=file[i];
	}
newf[i]='\0';


fp = fopen (file, "rb" );
if( !fp ) perror(file),exit(1);

fseek( fp , 0L , SEEK_END);
lSize = ftell( fp );
rewind( fp );

/* allocate memory for entire content */
buffer = calloc( 1, lSize+1 );
if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

/* copy the file into the buffer */
if( 1!=fread( buffer , lSize, 1 , fp) )
  fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);


printf("Enter the private key:");
scanf("%d",&key);



char store[1000];
long long int y;

for(i=0;i<strlen(buffer);i++)
	{
	size=0;
	while(buffer[i]!=' ' && buffer[i]!='\n')
		{
		temp[size]=buffer[i];
		size++;
		i++;	
		}

	x=0;
	for(j=0;j<size;j++)
		{
		x+=(int)((temp[j]-'0'))*pow(10,size-j-1);		
		}
	y = compute(x,key);	
	store[count]=(char)y;
	count++;
	}


newfile = fopen(newf,"w+");
if(!newfile)
        printf("Failed to make decrypted file");

else
        {
       
        for(i=0;i<count;i++)
                {
                fprintf(newfile,"%c",store[i]);
                }        
        fclose(newfile);

        status = remove(file);

        if(status!=0)
        printf("Not able to delete your encrypted file");

        fclose(fp);
        }
printf("\n");

free(buffer);

}
