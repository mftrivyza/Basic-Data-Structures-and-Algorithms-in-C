#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tf *tp;
 struct tf
 {
       int am;
       tp next;
 };
 
tp sp,bp; 

void pushback(tp *sp,tp bp);
void popfront(tp *sp,tp bp);
void print1(tp sp);
void print2(tp sp);

int main(void)
{
    char fry,fry2;
    fry='a';
    
    sp = NULL;
    bp = NULL;
    
    while(fry!='q')
    {
                   printf("\n Previous Fry %c \n",fry);
                   if(fry!='q')
                   {
                               printf("\n Give new choice \n");
                               printf("\n (i to 'PUSHBACK', d to 'POPFRONT', p to 'PRINT_1', w to 'PRINT_2', q to 'QUIT') \n");
                               
                               fry='a';
                               fflush(stdin);
                               fry=getchar();
                               
                               if(fry=='q')
                               {
                                           printf("\n QUIT \n");
                               }
                               if(fry=='i')
                               {
                                           printf("\n PUSHBACK \n");
                                           pushback(&sp,bp);
                               }
                               if(fry=='d')
                               {
                                           printf("\n POPFRONT \n");
                                           popfront(&sp,bp);
                               }            
                               if(fry=='p')
                               {
                                           printf("\n PRINT_1 \n");
                                           print1(sp);
                               }
                               if(fry=='w')
                               {
                                           printf("\n PRINT_2 \n");
                                           print2(sp);
                               }
                   }
    }
    system ("pause");
    return 0;
}

void pushback(tp *sp,tp bp)
{
     tp temp,aux;
     int da;
     temp = (tp)malloc(sizeof(struct tf));
     
     printf("\n Give me the data (int): \n");
     scanf("%d",&da);
     getchar();
     
     temp->am = da;
     temp->next = NULL;
     printf("\n The data of temp is: %d \n",temp->am);
     
     if(((*sp) != NULL)&&((*sp)->next != NULL))
     {
                                         aux = (*sp);
                                         temp->next = aux;
                                         (*sp) = temp;
     }
     if(((*sp) != NULL)&&((*sp)->next == NULL))
     { 
                                         temp->next = (*sp);
                                         (*sp) = temp;
     }
     if((*sp) == NULL)
     {
                    (*sp) = temp;
                    (*sp)->next = NULL;
                    bp = temp;
                    printf("\n First: %d \n",temp->am);
     }
}

void print1(tp sp)
{
     tp aux;
     aux = sp;
     
     while(aux != NULL)
     {
                     printf("\n Current is: %d ",aux->am);
                     aux = aux->next;
     }
     if(sp == NULL)
     {
        printf("\n The Stack Pointer is NULL. \n");
     }    
}

void print2(tp sp)
{
     if(sp != NULL)
     {
       printf("\n Data is: %d ",sp->am);
       if(sp->next != NULL)
       {
                     print2(sp->next);
       }
     }
     else
     {
        printf("\n The Stack Pointer is NULL. \n");
     }
}

void popfront(tp *sp,tp bp)
{
     tp aux;
     
     if(((*sp) != NULL)&&((*sp)->next == NULL))
     {
                  free(*sp);
                  free(bp);
                  (*sp) = NULL;
                  bp = NULL;                                                        
     }
     if(((*sp) != NULL)&&((*sp)->next != NULL))
     {
     			  aux = (*sp);   
                  (*sp) = (*sp)->next;
                  free(aux);   
                  aux = NULL;
     }
     if((*sp) == NULL)
     {
                  printf("\n The Stack Pointer is NULL. \n");
     }
}
