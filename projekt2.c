#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int s1,s2,tab[2][10];

void *w1()
{
  s1=0;
  for(int i=0;i<10;i++)
  {
	 s1+=tab[0][i];
	 printf("W1: Suma %d dla elementu %d\n",s1, i+1);
	 sleep(1);
  }
  printf("ID watku 1: %u, Suma watek 1(pierwszy wiersz): %d\n",pthread_self(),s1);
  pthread_exit((void *)0);
}

void *w2()
{
  s1=0;
  for(int i=0;i<10;i++)
  {
    s2+=tab[1][i];
	printf("W2: Suma %d dla elementu %d\n", s2, i + 1);
	sleep(1);
  }
  printf("ID watku 2: %u, Suma watek 2(drugi wiersz): %d\n",pthread_self(),s2);
  pthread_exit((void *)0);
}

int main()
{
  pthread_t tid1,tid2;
  int *kod;
  srand(time(NULL));
  
  for(int i=0;i<2;i++)
    for(int j=0;j<10;j++)
      tab[i][j] = rand()%60;

  printf("\nID Watku Glownego: %u\n\n", pthread_self());

  if(pthread_create(&tid1,NULL,w1,NULL)==-1)
  {
    perror("Blad tworzenia watku");
    exit(1);
  }
 
  if(pthread_create(&tid2,NULL,w2,NULL)==-1)
  {
    perror("Blad tworzenia watku");
    exit(1);
  }
  
  if(pthread_join(tid1,(void *)&kod)==-1)
  {
    perror("Blad przylaczenia watku");
    exit(2);
  }
  
  if(pthread_join(tid2,NULL)==-1)
  {
    perror("Blad przylaczenia watku");
    exit(2);
  }
  
  printf("Suma1 + Suma2 =%d\n",s1+s2);
  printf("Kod powrotu pierwszego watku: %u\n",kod);
  return 0;
}


