#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tf *tp;

 struct tf
 {
       int am;
       tp next;
 };

tp h,t; 

void insert(tp *h,tp t);
void delete(tp *h,tp t);
void print1(tp h);
void print2(tp h);

int main(void)
{
    char fry,fry2;
    fry='a';
    h=NULL;
    t=NULL;
    
    while(fry!='q')
    {
                   printf("\n Previous Fry %c \n",fry);
                   if(fry!='q')
                   {
                               printf("\n Give a new choice: \n");
                               printf("\n (i to 'INSERT', d to 'DELETE', p to 'PRINT_1', w to 'PRINT_2', q to 'QUIT') \n");
                               printf("\n ");
                               
                               fry='a';
                               fflush(stdin);
                               fry=getchar();
                               
                               if(fry=='q')
                               {
                                           printf("\n QUIT \n");
                               }
                               if(fry=='i')
                               {
                                           printf("\n INSERT \n");
                                           insert(&h,t);
                               }
                               if(fry=='d')
                               {
                                           printf("\n DELETE \n");
                                           delete(&h,t);
                               }            
                               if(fry=='p')
                               {
                                           printf("\n PRINT_1 \n");
                                           print1(h);
                               }
                               if(fry=='w')
                               {
                                           printf("\n PRINT_2 \n");
                                           print2(h);
                               }
                   }
    }
    system ("pause");
    return 0;
}

void insert(tp *h,tp t)
{
     tp temp,aux;
     int da;
     temp = (tp)malloc(sizeof(struct tf));
     
     printf("\n Give me the AM integer \n");
     scanf("%d",&da);
     getchar();
     
     temp->am = da;
     temp->next = NULL;
     printf("\n The AM of temp is %d \n",temp->am);
     
     if(((*h) != NULL) && (temp->am > (*h)->am))
     {
                  aux = (*h);
                  while((aux->next != NULL)&&(aux->next->am < temp->am))
                  {
                              aux = aux->next;
                  }
                  temp->next = aux->next;
                  aux->next = temp;
     }
     if(((*h) != NULL)&&(temp->am < (*h)->am))
     {
                  printf("\n I DO QUEUE \n");
				  temp->next = (*h);
                  (*h) = temp;
     }
     if((*h) == NULL)
     {
                   //printf("\n The head is NULL \n");
                   (*h) = temp;
                   (*h)->next = NULL;
                   //t = temp;
                   printf("\n First %d \n",temp->am);
     }
}

void print1(tp h) 
{
     tp aux;
     aux = h;
     while(aux != NULL)
     {
                    printf("\n Current is %d ",aux->am);
                    aux = aux->next;
     }
     if(h == NULL)
     {
        printf("\n The head is NULL \n");
     }    
}

void print2(tp h) 
{
     if(h != NULL)
     {
       printf("\n AM is %d ",h->am);
       if(h->next != NULL)
       {
                     print2(h->next);
       }
     }
     else
     {
        printf("\n The head is NULL \n");
     }
}

void delete(tp *h,tp t)
{
     tp temp,aux;
     int da;
     
     printf("\n Give me the AM integer \n");
     scanf("%d",&da);
     getchar();
     
     if(*h == NULL)
     {
                 printf("\n The head is NULL, so the AM integer does not exist \n");
     }
     if(((*h) != NULL)&&((*h)->next == NULL))
     {
                 if((*h)->am == da)
                 {
                           free(*h);
                           (*h) = NULL;
                           //free(t);
                           //t=NULL;
                 }   
                 else
                 {
                           printf("\n The AM integer does not exist \n");
                 }                                                      
     }
     if(((*h) != NULL)&&((*h)->next != NULL))
     {
                 if((*h)->am == da)
                 {
                             aux = (*h);
                             (*h) = (*h)->next;
                             free(aux); 
                             aux = NULL;
                 }
                 else if((*h)->am != da)
                 {
                             aux = (*h);
                             while((aux->next != NULL)&&(aux->next->am != da))
                             {
                                               aux = aux->next;
                             }
                             if ((aux->next != NULL)&&(aux->next->am == da))
                             {
                                               temp = aux->next;
                                               aux->next = temp->next;
                                               free(temp);
                                               temp = NULL;
                             }
                             else
                             {
                                 printf("\n The AM integer does not exist \n");
                             } 
                 }                
     }
}
