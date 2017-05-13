#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#define NUMOFPHILOSOPHERS 5
#define NUMOFFORKS 5


int hasEaten[5] = {0};

struct timeval te,tf;

int totalTime =0;
int philCount =0;
int peakTime = 0;

void *function(int n);

pthread_t philosophers[NUMOFPHILOSOPHERS];
pthread_mutex_t forks[NUMOFFORKS];
pthread_mutex_t total = PTHREAD_MUTEX_INITIALIZER;

int main(){
    int i,k;

    for(i=0;i<NUMOFFORKS;i++){

        pthread_mutex_init(&forks[i],NULL);

    }


    for(i=0;i<NUMOFPHILOSOPHERS;i++){

        pthread_create(&philosophers[i],NULL,(void *)function,(void *)i);

    }


    for(i=0;i<NUMOFPHILOSOPHERS;i++){

        pthread_join(philosophers[i],NULL);

    }


    printf("All of the philsosophers are done eating! \n");
    printf("Average waiting time was %d ms \n",totalTime / NUMOFPHILOSOPHERS);


}



void *function(int n){


    while(1){
        clock_t start_time, end_time, elapsed;
        printf("philosopher %d is thinking \n", n);
        int randomThinking;
        randomThinking = rand()%15;
        sleep(randomThinking);
        int s,m;
        printf("philosopher %d is HUNGRY!!!!!\n",n);
        gettimeofday(&te, NULL); // get current time
        long long millisecondsStart = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds

        if(hasEaten[n]==1){
            sleep(rand()%15+1);
            printf("phil %d has to wait \n", n );
        }

        pthread_mutex_lock(&forks[n]);
        printf("philosopher %d got right fork-forkNO.->%d\n", n,n);

        pthread_mutex_lock(&forks[(n+1)%(NUMOFPHILOSOPHERS )]);
        printf("philosopher %d got left fork-forkNO.->%d\n", n,(n+1)%(NUMOFPHILOSOPHERS ));

        gettimeofday(&tf, NULL); // get current time

        long long millisecondsEnd = tf.tv_sec*1000LL + tf.tv_usec/1000; // caculate milliseconds

        long long diff = millisecondsEnd - millisecondsStart;

        printf("waiting time for philosopher %d is : %lld ms \n", n,diff) ;


        pthread_mutex_lock(&total);

        if(diff>peakTime){
            peakTime = diff;
        }

        totalTime += diff;
        philCount++;
        printf("philCount: %d \n",philCount);
        if(philCount == 5){
            philCount =0;
            printf("average waiting time is: %d \n",totalTime/NUMOFPHILOSOPHERS);
            printf("peak time is:%d \n", peakTime);
            peakTime = 0;
            int i;
            for( i=0;i<5;i++){
                hasEaten[i] =0;
            }
            printf("array reinitialized \n");
        }
        pthread_mutex_unlock(&total);



        elapsed = (end_time - start_time) ;
        int msec = elapsed * 1000 /CLOCKS_PER_SEC;


        int randomEat;
        randomEat = rand()%10;
        printf("philosopher %d is going to eat for %d s! \n", n,randomEat +1);
        sleep(randomEat + 1);
        pthread_mutex_unlock(&forks[n]);
        printf("philosopher %d has put down fork no. %d \n", n, n);
        pthread_mutex_unlock(&forks[(n+1)%(NUMOFPHILOSOPHERS )]);
        printf("philosopher %d has put down fork no. %d \n", n, (n+1)%NUMOFPHILOSOPHERS);
        printf("philosopher %d is done eating! \n", n);
        hasEaten[n] = 1;

    }
}
