#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i,Pinakas[10],Hsize;
char c;
void HEAPIFY(int i);
void INSERT_HEAP(void);
void BUILD_HEAP(void);
void HEAPSORT(void);
void PRINT_ARRAY(void);

int main(void)
{
    c='*';
    while (c!='q')
    {
          printf("\n Insert (i), Build heap (b), Heapsort (s), Print (p), Quit (q): \n");
          scanf("%c",&c);
          if(c=='i')
                    INSERT_HEAP();
          else if(c=='b')
                    BUILD_HEAP();
          else if(c=='s')
                    HEAPSORT();
          else if (c=='p')
                    PRINT_ARRAY();
          printf("\n Press any key to continue... \n");
          getchar();
          getchar();
     }
     system("pause");
     return 0; 
}

void HEAPIFY(int i)
{
     int l,k,r,largest;
     l=2*i+1;
     r=l+1;
     if((l<=Hsize)&&(Pinakas[l]>Pinakas[i]))
     {
                      largest=l;
     }
     else
     {
                      largest=i;
     }
     if((r<=Hsize)&&(Pinakas[r]>Pinakas[largest]))
     {
                      largest=r;
     }
     if(largest!=i)
     {
                      k=Pinakas[i];
                      Pinakas[i]=Pinakas[largest];
                      Pinakas[largest]=k;
                      HEAPIFY(largest);
     }
}

void INSERT_HEAP()
{
     int i,k;
     printf("\n Insert 10 new integers to the array. \n");
     for(i=0;i<=9;i++)
     {
                      scanf("%d",&k);
                      Pinakas[i]=k;
                      printf("\n The new integer you inserted is: %d \n",Pinakas[i]);
     }
     Hsize=9;
}

void BUILD_HEAP()
{
     int m;
     for(m=4;m>=0;m--)
     {
                      HEAPIFY(m);
     }
}

void HEAPSORT()
{
     int q,p;
     BUILD_HEAP();
     for(q=9;q>=1;q--)
     {
                      p=Pinakas[0];
                      Pinakas[0]=Pinakas[q];
                      Pinakas[q]=p;
                      Hsize=Hsize-1;
                      HEAPIFY(0);
     }
     printf("\n The array was sorted. \n");
     PRINT_ARRAY();
     Hsize=9;
}

void PRINT_ARRAY()
{
     int j;
     printf("\n The array is consisted of: \n");
     for(j=0;j<10;j++)
     {
                      printf("\n A[%d]=%d \n",j,Pinakas[j]);
     }
}
