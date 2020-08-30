#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tf *tp;

 struct tf
 {
       int am;
       tp next, previous;
 };

tp h,t,temp,to;
int da;

void insert(tp *h,tp to);
void delete(tp *h,tp t);
void print(tp h);
void print_2(tp h);

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
                               scanf("%c",&fry);
			       getchar();

                               if(fry=='q')
                               {
                                           printf("\n QUIT \n");
                               }
                               if(fry=='i')
                               {
                                           printf("\n INSERT \n");

                                           printf("\n Give me the AM integer \n");
                                           scanf("%d",&da);
                                           getchar();

                                           temp = (tp)malloc(sizeof(struct tf));
                                           temp->am = da;
                                           temp->next = NULL;
                                           temp->previous = NULL;
                                           printf("\n The AM of temp is %d \n",temp->am);
 
                                           insert(&h,temp);
                               }
                               if(fry=='d')
                               {
                                           printf("\n Give me the AM integer \n");
                                           scanf("%d",&da);
                                           getchar();

                                           printf("\n DELETE \n");
                                           delete(&h,t);
                               }
                               if(fry=='p')
                               {
                                           printf("\n PRINT \n");
                                           print(h);
                               }
                               if(fry=='w')
                               {
                                           printf("\n PRINT2 \n");
                                           print_2(h);
                               }
                   }
    }
    //system ("pause");
    return 0;
}

void insert(tp *h, tp to)
{
     tp aux;
     
     if((*h) != NULL) 
     {
          if(((*h)->next) != NULL)
          {
               if(temp->am > (*h)->am)
               {                 
                        aux = (*h);
                        insert(&(aux->next),t);
               }
               else
               {
                   if((*h)->previous == NULL)
                   {
                        temp->next = (*h);
                        temp->previous = NULL;
                        (*h)->previous = temp;
                        (*h) = temp;
                   }
                   else
                   {
                        aux = (*h);
                        temp->next = aux;
                        temp->previous = aux->previous;
                        aux->previous = temp;
                        (*h) = temp;
                   }
               }
          }
          else
          {
               if(temp->am > (*h)->am)
               {
                     temp->previous = (*h);
                     temp->next = NULL;
                     (*h)->next = temp;
               }
               else
               {
                     aux = (*h);
                     (aux)->previous = temp;
                     (aux)->next = NULL;
                     temp->next = (aux);
                     temp->previous = NULL;
                     (*h) = temp;
               }
           }
     }
     else
     {
           //printf("\n The head is NULL \n");
           (*h) = temp;
           (*h)->next = NULL;
           (*h)->previous = NULL;
           printf("\n First %d \n",temp->am);
     }  

}

void delete(tp *h,tp t)
{
     tp aux, aux1, aux2;

     if(((*h) != NULL)&&((*h)->next != NULL))
     {
                 if((*h)->am != da)
                 {
                             aux = (*h);
                             delete(&(aux->next),t);
                 }   
                 else if((*h)->am == da)
                 {
                      if((*h)->previous != NULL)
                      {
                             aux = (*h);
                             (*h) = (*h)->next;
                             aux1 = aux->previous;
                             aux1->next = (*h);
                             (*h)->previous = aux1;
                             free(aux); 
                             aux = NULL;
                       }
                       else
                       { 
                             aux = (*h);
                             (*h) = (*h)->next;
                             (*h)->previous = NULL;
                             free(aux); 
                             aux = NULL;
                       }
                 }   
                 else
                 {
                             printf("\n The AM integer does not exist \n");
                 }           
     }
     else if(((*h) != NULL)&&((*h)->next == NULL))
     {
                 if((*h)->am == da)
                 {
                           free(*h);
                           (*h) = NULL;
                           printf("\n The head is now NULL \n");
                 }   
                 else
                 {
                           printf("\n The AM integer does not exist \n");
                 }                                                      
     }
     else if((*h) == NULL)
     {
                 printf("\n The head is NULL, so the AM integer does not exist \n");
     }
}

void print(tp h) 
{
     if(h != NULL)
     {
                 printf("\n AM is %d ",h->am);

                 if(h->next != NULL)
                 {
                           print(h->next);
                 }
     }
     else
     {
                 printf("\n The head is NULL \n");
     }
}

void print_2(tp h) 
{

     tp aux;
 
     if(h != NULL)
     {
                 aux = h; 
                 while(aux->next != NULL)
                 {
                     aux = aux->next;
                 }
                 while(aux != NULL)
                 {
                     printf("\n AM is %d ",aux->am);
                     aux = aux->previous;
                 }
     }
     else
     {
                 printf("\n The head is NULL \n");
     }
}
