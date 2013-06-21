/*
This program takes filename and public key to encrypt the file using RSA
Deletes the original file and store encypted data in a new file named original filename appended by _enc
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int p=61,q=53,n=3233;

int compute(int y,int q)
{
if(q==2)
	return y*y;

if(q==1)
	return y;

int x=compute(y,q/2);

if(q%2==0)
	return (x*x)%n;

else
	return (((x*x)%n)*(y))%n;
}


int main()
{
char file[100],newf[100];
int status,i,x,y,key,store[1000],count=0;

printf("Enter the file to encrypt:");
scanf("%s",file);

for(i=0;i<strlen(file);i++)
	newf[i]=file[i];

newf[i]='_';
newf[i+1]='e';
newf[i+2]='n';
newf[i+3]='c';
newf[i+4]='\0';

printf("Enter the public key:");
scanf("%d",&key);

FILE *fp,*newfile;
long lSize;
char *buffer;

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




for(i=0;i<strlen(buffer);i++)
	{
	x = (int)buffer[i];
	y = compute(x,key);	
	store[count]=y;
	count++;
	}


newfile = fopen(newf,"w+");
if(!newfile)
	printf("Failed to make encrypted file");

else
	{
	for(i=0;i<strlen(buffer);i++)
		{
		fprintf(newfile,"%d ",store[i]);
		}
	fclose(newfile);

	status = remove(file);

	if(status!=0)
        printf("Not able to delete your plaintext file");

	fclose(fp);
	}
printf("\n");

free(buffer);

}
