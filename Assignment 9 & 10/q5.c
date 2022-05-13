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
int philo=-90;
void * transaction(void * num){
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
    if(philo!=identity){
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

void * detect_deadlock(void * num){
    srand ( time(NULL) );
    while(count<1){
        bool indi = true;
        fr(0,2){
            if(first[i]==true && second[i]==false){

            }
            else{
                indi = false;
            }
        }
        // If there is deadlock
        if(indi){
            printf("\nBoth tables are locked.. User report a DEADLOCK");
            printf("\n Development  team decides to receive consultancy service from an experienced database administrator");
            printf("\nDatabase administrator looks at locks and decides to unlock one of them by a rollback");
            printf("\n<<<<<<      ROLLBACK A TRANSACTION    >>>>>>\n");
            philo = rand() % 2;
            sem_post(&table[philo]);
            first[philo] = false;
            printf("\nTransaction %d rolled back (releases %d table)",philo,philo);
            count++;
        }
    }
}

int main(){
	fr(0,2){
        first[i] = false;
        second[i] = false;
	}
	int i,a[2];
    int x=2;
	
    pthread_t dl;
    pthread_create(&dl,NULL,detect_deadlock,(void *)&x);
	
	sem_init(&room,0,2);
	
	fr(0,2){
		sem_init(&table[i],0,1);
	}	
	fr(0,2){
		a[i]=i;
		pthread_create(&tid[i],NULL,transaction,(void *)&a[i]);
	}
	fr(0,2){
        pthread_join(tid[i],NULL);
    }		
}
