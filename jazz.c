#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_CUSTOMERS 300

pthread_t customer_tid[MAX_CUSTOMERS];

sem_t count_sema;
sem_t doorman;
int customer_count = 0;

void enter_club( int customer_number )
{
    sem_wait( & doorman );
    sem_wait( &count_sema );
    {
        customer_count ++; 
        assert( customer_count < 9);
    }    
    printf("Customer %d enters the club \n", customer_number );
    sem_post( &count_sema );
}

void hangout( )
{
    sleep( rand() % 30 );
}

void exit_club( int customer_number )
{
    sem_wait( &count_sema );
    {
        customer_count -- ;
    }
    sem_post( &count_sema );
    printf("Customer %d exits the club \n", customer_number );
    sem_post( & doorman );
}

void * customer ( void * arg )
{
    int customer_number = (int)arg;
    enter_club( customer_number );
    hangout( );
    exit_club( customer_number );
    return NULL;
}

int main()
{
    int i;
    srand( time( NULL ) ); 

    sem_init( &count_sema, 0, 1 );
    sem_init( &doorman, 0, 8 );
    for( i = 0; i < MAX_CUSTOMERS; i++ )
    {
        pthread_create( &customer_tid[i], NULL, customer, (void*)i );
    }

    for( i = 0; i < MAX_CUSTOMERS; i++ )
    {
        pthread_join( customer_tid[i], NULL );
    }
}