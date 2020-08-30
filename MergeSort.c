#include <stdio.h>
#define max 10

int A[max];
int B[max];
void merge(int low, int mid, int high);
void mergesort(int low, int high); 

int main() 
{ 
   int i,k;
   printf("\n Add %d new integers to the array. \n", max);
   for(i=0; i < max; i++)
   {
            scanf("%d",&k);
            A[i]=k;
            printf("\n The new integer you added: %d \n",A[i]);
   }
   
   printf("\n Unsorted array: \n");
   printf("\n ");
   
   for(i = 0; i < max; i++)
   {
      printf("%d ", A[i]);
   }

   mergesort(0, max-1);
   
   printf("\n ");
   printf("\n Sorted array: \n");
   printf("\n ");
   
   for(i = 0; i < max; i++)
   {
      printf("%d ", B[i]);
   }
   
   printf("\n ");
   system ("pause");
   return 0;
}

void merge(int low, int mid, int high) 
{
   int p, q, i;
   p = low; 
   q = mid; 
   i = low;

   while( (p < mid) && (q < high+1) ) 
   {
      if(A[p] <= A[q])
      {
         B[i] = A[p];
         p=p+1;
         i=i+1;
      }
      else
      {
         B[i] = A[q];
         q=q+1;
         i=i+1;
      }
   }
   
   while(p < mid) 
   {   
      B[i] = A[p];
      i=i+1;
      p=p+1;
   }

   while(q < high+1)
   {   
      B[i] = A[q];
      i=i+1;
      q=q+1;
   }

   for(i = low; i < high+1; i++)
      A[i] = B[i];
}

void mergesort(int low, int high) 
{
   int mid;
   
   if(low < high) 
   {
      mid = low + (high-low+1) / 2;
      mergesort(low, mid-1);
      mergesort(mid, high);
      merge(low, mid, high);
   } 
   else 
   { 
      return;
   }   
}
