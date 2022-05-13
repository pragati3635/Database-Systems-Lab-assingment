#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int database = 0; 
void* transaction(int id){
    printf("transaction %d has started\n", id);
    sleep(5);
    database++;
    printf("Database is updated to the value %d now\n", database);
    sleep(5);
    printf("transaction %d has ended\n", id);
}

int main(){
    pthread_t t1, t2,t3,t4;
    pthread_create(&t1, NULL, transaction, (void*)1); 
    pthread_create(&t2, NULL, transaction, (void*)2); 
    pthread_create(&t3, NULL, transaction, (void*)3); 
    pthread_create(&t4, NULL, transaction, (void*)4); 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    return 0;
} 