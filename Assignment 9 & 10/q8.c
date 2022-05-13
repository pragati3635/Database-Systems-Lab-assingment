#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>
#define fr(a,b) for(int i = a; i < b; i++)

sem_t room;
sem_t table[2];
bool first[2];
bool second[2];
int count = 0;
pthread_t tid[2];
int timestamp[2];
int philo=-90;
void * transaction0(void * num){
    srand ( time(NULL) );
	int identity=*(int *)num;

	sem_wait(&room);
    printf("\nTransaction %d has started",identity);

    sleep((rand() % 2) + 1);
	sem_wait(&table[identity]);
    first[identity] = true;
    printf("\ntransaction %d is has updated the first table %d ",identity,identity);

    sleep(10);

	sem_wait(&table[(identity+1)%2]);
   
    second[identity]=true;
    printf("\ntransaction %d is has updated the second table %d",identity,(identity+1)%2);

	sleep((rand() % 2) + 1);
	printf("\ntransaction %d has  completed",identity);

	sem_post(&table[(identity+1)%2]);
    second[identity]= false;
	sem_post(&table[identity]);
    first[identity] = false;
	sem_post(&room);
    
}
void * transaction1(void * num){
    srand ( time(NULL) );
	int identity=*(int *)num;

	sem_wait(&room);
    printf("\nTransaction %d has started",identity);

    sleep((rand() % 2) + 1);
	sem_wait(&table[identity]);
    first[identity] = true;
    printf("\ntransaction %d is has updated the first table %d ",identity,identity);

    sleep(10);
    if(timestamp[1]>=timestamp[0]){
        printf("\n timestamp of transaction 1 is greater than 0 so ROLLBACK!!!");
        sem_post(&table[1]);
        first[1] = false;
        printf("\nTransaction 1 rolled back (releases 1st table)");
    }
    
	else{
        sem_wait(&table[(identity+1)%2]);
        second[identity]=true;
        printf("\ntransaction %d is has updated the second table %d",identity,(identity+1)%2);

        sleep((rand() % 2) + 1);
        printf("\ntransaction %d has  completed",identity);

        sem_post(&table[(identity+1)%2]);
        second[identity]= false;
        sem_post(&table[identity]);
        first[identity] = false;
        sem_post(&room);
    }
    
}



int main(){
	fr(0,2){
        first[i] = false;
        second[i] = false;
	}
	int i,a[2];
    int x=2;
	sem_init(&room,0,2);
	
	fr(0,2){
		sem_init(&table[i],0,1);
	}	
	fr(0,1){
		a[i]=i;
        timestamp[i] = i;
		pthread_create(&tid[i],NULL,transaction0,(void *)&a[i]);
	}
    fr(1,2){
        a[i]=i;
        timestamp[i] = i;
		pthread_create(&tid[i],NULL,transaction1,(void *)&a[i]);

    }
	fr(0,2){
        pthread_join(tid[i],NULL);
    }		
}
