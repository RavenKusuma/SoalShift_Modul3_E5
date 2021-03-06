#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid1;
pthread_t tid2;

//condition1: p1 input
//condition2: p2 tebak, p2 input
//condition3: p1 tebak
//condition4: game over

int field1[17];
int field2[17];
int ranjau,banyak;
char player1[100];
char player2[100];
int stok1=16,stok2=16;
int nilai1=0,nilai2=0;
int condition;

void* p1(void *arg)
{
	while(1)
	{
		printf("Nama : %s\nskor : %d\nNama : %s\nskor : %d\n",player1,nilai1,player2,nilai2);
		condition=1;
        	printf("pemain 1,Banyak ranjau(max 16) => ");
        	scanf("%d",&banyak);
        	for(int i=0;i<banyak;i++)
		{
			printf("Letakan ranjau di => ");
	        	scanf("%d",&ranjau);
            		if(field1[ranjau]==0)stok1--;
            		field1[ranjau]=1;
        	}
		condition=2;
		while(condition==2||condition==4)
		{
          		if(condition==4)
			{
				return NULL;
			}
        	}
        	printf("pemain 1,tebak =>  ");
		scanf("%d",&ranjau);
        	if(field2[ranjau]==0)
		{
	            	printf("tebakkan %s benar, poin %s ditambah 1\n",player1,player1);
	            	++nilai1;
	        }
	        else
		{
	        	printf("tebakkan %s salah, poin %s ditambah 1\n",player1,player2);
	         	++nilai2;
        	}
        	if(nilai1==10 || nilai2 == 10 || stok1==0 || stok2==0)
		{
			condition=4;
			return NULL;
		}
	}
    	return NULL;
}

void* p2(void *arg)
{
	while(1)
	{
        	condition=1;
        	while(condition==1||condition==4)
		{
        		if(condition==4)
			{
				return NULL;
			}
       		}
        	printf("pemain 2,tebak => ");
        	scanf("%d",&ranjau);
        	if(field1[ranjau]==0)
		{
    		        printf("tebakkan %s benar, poin %s ditambah 1\n",player2,player2);
        		++nilai2;
        	}
	        else
		{
	        	printf("tebakkan %s salah, poin %s ditambah 1\n",player2,player1);
            		++nilai1;
        	}
        	if(nilai1==10 || nilai2== 10 || stok1==0 || stok2==0)
		{
			condition=4;
			return NULL;
		}
        	printf("Nama : %s\nskor : %d\nNama : %s\nskor : %d\n",player1,nilai1,player2,nilai2);
        	printf("pemain 2,Banyak ranjau(max 16) => ");
        	scanf("%d",&banyak);
		for(int i=0;i<banyak;i++)
		{
			printf("Letakan ranjau di => ");
	        	scanf("%d",&ranjau);
            		if(field2[ranjau]==0)stok2--;
            		field2[ranjau]=1;
        	}
        	condition=3;
	}
	return NULL;

}


int main()
{
	while(1)
	{
    		printf("Masukan Nama Player1 => ");
		scanf("%s",player1);
		printf("Masukan Nama Player2 => ");
		scanf("%s",player2);
    		nilai1=0;
    		nilai2=0;
    		for(int i=1;i<=16;++i)
		{
    			field1[i]=0;
        		field2[i]=0;
    		}
    		pthread_create(&(tid1), NULL, &p1, NULL);
    		pthread_create(&(tid2), NULL, &p2, NULL);
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		while(condition!=4);
		printf("Nama : %s\nskor : %d\nNama : %s\nskor : %d\n",player1,nilai1,player2,nilai2);
	}
	return 0;
}
