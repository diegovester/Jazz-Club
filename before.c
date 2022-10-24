#include <semaphore.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_CUSTOMERS 300

pthread_t customer_tid[MAX_CUSTOMERS];

int customer_count = 0;

void enter_club( )
{
    customer_count ++; 
    assert( customer_count < 9);
}

void hangout( )
{
    sleep( rand() % 30 );
}

void exit_club()
{
    customer_count -- ;
}

void * customer ( void * arg )
{
    enter_club( );
    hangout( );
    exit_club( );
    return NULL;
}

int main()
{
    int i;
    srand( time( NULL ) ); 
    for( i = 0; i < MAX_CUSTOMERS; i++ )
    {
        pthread_create( &customer_tid[i], NULL, customer, NULL );
    }

    for( i = 0; i < MAX_CUSTOMERS; i++ )
    {
        pthread_join( customer_tid[i], NULL );
    }
}