#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 31

typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct tf *tp;

 struct tf
 {
       int da_i,da_j;
       int level;
       bool active, in;
       tp next, previous, up, down, father;
 };

tp column[MAX];
tp row[MAX];

tp h,t,temp,temp_2,to;
tp header, tempp, too;
int i,j,root;
bool exists;

void initialize_sparse_array(void);

void insert_row(tp *h,tp to);
void insert_column(tp *h,tp to);
void delete_row(tp *h,int da);
void delete_column(tp *h,int da);

int number_of_vertices(void);
int number_of_edges(void);

void print_rows(tp h);
void print_columns(tp h);

void spanning_tree(tp *h);
void print_active_edges(tp h);
void print_inactive_edges(tp h);
void print_spanning_tree(void);
void delete_spanning_tree(void);

void find_circles(void);
void insert_queue_path(tp *header,tp too);
void delete_queue_path(tp *header);
void print_queue(tp header);

int main(void)
{
    char fry,fry2;
    fry='a';
    h=NULL;
    t=NULL;
    exists = FALSE;
    
    initialize_sparse_array();

    do
    {
           printf("\n Give a new choice: \n");
           printf("\n 1 to 'INSERT_EDGE', 2 to 'DELETE_EDGE', 3 to 'PRINT_ROWS', 4 to 'PRINT_COLUMNS' ");
           printf("\n 5 to 'CREATE_SPANNING_TREE', 6 to 'PRINT_ACTIVE_EDGES', 7 to 'PRINT_SPANNING_TREE', 8 to 'DELETE_SPANNING_TREE', 9 to 'FIND_CICLES' ");
           printf("\n q to 'QUIT' \n");
           printf("\n ");
                               
           fry='a';
           fflush(stdin);
           scanf("%c",&fry);
           //getchar();

           switch(fry)
           {

                             case 'q':
                             {
                                          printf("\n QUIT \n");
                                          break;
                             }
                             case '1':
                             {
                                           do{
                                               printf("\n INSERT \n");
                                               printf("\n Give me the row integer form 1 to 30: ");
                                               scanf("%d",&i);
                                               printf(" Give me the column integer form 1 to 30: ");
                                               scanf("%d",&j);
                                               getchar();
                                           }while(!(i >= 1 && i <= (MAX-1)) || !(j >= 1 && j <= (MAX-1)) || (i == j));
                                          
                                           temp = (tp)malloc(sizeof(struct tf));

                                           temp->da_i = i; temp->da_j = j;
                                           temp->next = NULL; temp->previous = NULL; temp->up = NULL; temp->down = NULL;
                                           temp->active	= FALSE;
 
                                           insert_row(&(column[i]),temp);
                                           insert_column(&(row[j]),temp);

                                           temp_2 = (tp)malloc(sizeof(struct tf));

                                           temp_2->da_i = j; temp_2->da_j = i;
                                           temp_2->next = NULL; temp_2->previous = NULL; temp_2->up = NULL; temp_2->down = NULL;
                                           temp_2->active = FALSE;

                                           insert_row(&(column[j]),temp_2);
                                           insert_column(&(row[i]),temp_2);

                                           number_of_vertices();
                                           number_of_edges();
                                           break;
                             }
                             case '2':
                             {
                                           do{
                                               printf("\n DELETE \n");
                                               printf("\n Give me the row integer form 1 to 30: ");
                                               scanf("%d",&i);
                                               printf(" Give me the column integer form 1 to 30: ");
                                               scanf("%d",&j);
                                               getchar();
                                           }while(!(i >= 1 && i <= (MAX-1)) || !(j >= 1 && j <= (MAX-1)) || (i == j));
                                          
                                           delete_row(&(column[i]),j);
                                           delete_column(&(row[j]),i);

                                           delete_row(&(column[j]),i);
                                           delete_column(&(row[i]),j);

                                           number_of_vertices();
                                           number_of_edges();
                                           break;
                             }
                             case '3':
                             {
                                           printf("\n PRINT_ROWS \n");
				           for(int k = 1; k < MAX; k++)
                                           {
                                                printf("\n Row %d: ", k);
                                                print_rows(column[k]);
                                                printf("\n");
                                           }
                                           break;
                             }
                             case '4':
                             {
                                           printf("\n PRINT_COLUMNS \n");
                                           for(int k = 1; k < MAX; k++)
                                           {
                                                printf("\n Column %d: ", k);
                                                print_columns(row[k]);
                                                printf("\n");
                                           }
                                           break;
                             }
                             case '5':
                             {
                                           do{
                                               printf("\n CREATE_SPANNING_TREE \n");
                                      
			                       printf("\n Insert Root Node: "); 
			                       scanf("%d", &root);
                                               getchar();
                                           }while(!(root >= 1 && root <= (MAX-1)));
                     
                                           column[root]->level = 0;
                                           column[root]->in = TRUE;
                                           column[root]->father = column[root];

                                           printf("\n level %d: root: %d \n",column[root]->level, root);
                                           printf("\n");

                                           spanning_tree(&column[root]);
                                           exists = TRUE;

                                           break;

                             }
                             case '6':
                             {
                                           printf("\n PRINT_ACTIVE_EDGES \n");
				           for(int k = 1; k < MAX; k++)
                                           {
                                                printf("\n Row %d: ", k);
                                                print_active_edges(column[k]);
                                                printf("\n");

                                                print_inactive_edges(column[k]); 
                                                printf("\n");
                                           }
                                           break;
                             }
                             case '7':
                             {
                                           printf("\n PRINT_SPANNING_TREE \n");
			                   print_spanning_tree();
                                           break;
                             }
                             case '8':
                             {
                                           printf("\n DELETE_SPANNING_TREE \n");
			                   delete_spanning_tree();
                                           exists = FALSE;
                                           break;
                             }
                             case '9':
                             {
                                           printf("\n FIND_CIRCLES_IN_SPANNING_TREE \n");
			                   find_circles();
                                           break;
                             }
                             default:
                             {
                                           printf("\n Please Try Again \n");
                                           break;
                             }
                }
    }while(fry != 'q');
    //system ("pause");
    return 0;
}

// initialize the sparse array
void initialize_sparse_array()
{
    for(int z = 1; z < MAX; z++)
    {
      row[z] = (tp)malloc(sizeof(struct tf));
      row[z]->da_i = 0;
      row[z]->da_j = z;
      row[z]->level = -1;
      row[z]->active = FALSE;
      row[z]->in = FALSE;
      row[z]->next = NULL;
      row[z]->previous = NULL;
      row[z]->up = NULL;
      row[z]->down = NULL;
      column[z] = (tp)malloc(sizeof(struct tf));
      column[z]->da_i = z;
      column[z]->da_j = 0;
      column[z]->level = -1;
      column[z]->active = FALSE;
      column[z]->in = FALSE;
      column[z]->next = NULL;
      column[z]->previous = NULL;
      column[z]->up = NULL;
      column[z]->down = NULL;
    } 
}

void insert_row(tp *h, tp to)
{
     tp aux;
     
     if((*h) != NULL) 
     {
          if(((*h)->next) != NULL)
          {
               if(to->da_j > (*h)->da_j)
               {                 
                        aux = (*h);
                        insert_row(&(aux->next),to);
               }
               else if(to->da_j < (*h)->da_j)
               {
                   if((*h)->previous == NULL)
                   {
                        to->next = (*h);
                        to->previous = NULL;
                        (*h)->previous = to;
                        (*h) = to;
                   }
                   else
                   {
                        aux = (*h);
                        to->next = aux;
                        to->previous = aux->previous;
                        aux->previous = to;
                        (*h) = to;
                   }
               }
               else
               {
                   printf("\n j already exists \n");
               }
          }
          else
          {
               if(to->da_j > (*h)->da_j)
               {
                     to->previous = (*h);
                     to->next = NULL;
                     (*h)->next = to;
               }
               else if(to->da_j < (*h)->da_j)
               {
                     aux = (*h);
                     (aux)->previous = to;
                     (aux)->next = NULL;
                     to->next = (aux);
                     to->previous = NULL;
                     (*h) = to;
               }
               else
               {
                   printf("\n j already exists \n");
               }
           }
     }
     else
     {
           (*h) = to;
           (*h)->next = NULL;
           (*h)->previous = NULL;
     }  
}

void insert_column(tp *h, tp to)
{
     tp aux;
     
     if((*h) != NULL) 
     {
          if(((*h)->down) != NULL) 
          {
               if(to->da_i > (*h)->da_i)
               {                 
                   aux = (*h);
                   insert_column(&(aux->down),to);
               }
               else if(to->da_i < (*h)->da_i)
               {
                   if((*h)->up == NULL)
                   {
                        to->down = (*h);
                        to->up = NULL;
                        (*h)->up = to;
                        (*h) = to;
                   }
                   else
                   {
                        aux = (*h);
                        to->down = aux;
                        to->up = aux->up;
                        aux->up = to;
                        (*h) = to;
                   }
               }
               else
               {
                   printf("\n i already exists \n");
               }
          }
          else
          {
               if(to->da_i > (*h)->da_i)
               {
                   to->up = (*h);
                   to->down = NULL;
                   (*h)->down = to;
               }
               else if(to->da_i < (*h)->da_i)
               {
                   aux = (*h);
                   (aux)->up = to;
                   (aux)->down = NULL;
                   to->down = (aux);
                   to->up = NULL;
                   (*h) = to;
               }
               else
               {
                   printf("\n i already exists \n");
               }
           }
     }
     else
     {
           (*h) = to;
           (*h)->down = NULL;
           (*h)->up = NULL;
     }  
}

void delete_row(tp *h, int da)
{
     tp aux, aux1;

     if(((*h) != NULL)&&((*h)->next != NULL))
     {
                 if((*h)->da_j != da)
                 {
                      aux = (*h);
                      delete_row(&(aux->next),da);
                 }   
                 else if((*h)->da_j == da)
                 {
                      if((*h)->previous != NULL)
                      {
                             aux = (*h);
                             (*h) = (*h)->next;
                             aux1 = aux->previous;
                             aux1->next = (*h);
                             (*h)->previous = aux1;
                       }
                       else
                       { 
                             aux = (*h);
                             (*h) = (*h)->next;
                             (*h)->previous = NULL;
                       }
                 }   
                 else
                 {
                       printf("\n The j integer does not exist \n");
                 }           
     }
     else if(((*h) != NULL) && ((*h)->next == NULL))
     {
                 if((*h)->da_j == da)
                 {
                       (*h) = NULL;
                 }   
                 else
                 {
                       printf("\n The j integer does not exist \n");
                 }                                                      
     }
     else if((*h) == NULL)
     {
                 printf("\n The row's head is NULL, so the j integer does not exist \n");
     }
}

void delete_column(tp *h,int da)
{
     tp aux, aux1;

     if(((*h) != NULL) && ((*h)->down != NULL))
     {
                 if((*h)->da_i != da)
                 {
                      aux = (*h);
                      delete_column(&(aux->down),da);
                 }   
                 else if((*h)->da_i == da)
                 {  
                      if((*h)->up != NULL)
                      {
                             aux = (*h);
                             (*h) = (*h)->down;
                             aux1 = aux->up; 
                             aux1->down = (*h);
                             (*h)->up = aux1;
                             free(aux); 
                             aux = NULL;
                       }
                       else
                       {   
                             aux = (*h);
                             (*h) = (*h)->down;
                             (*h)->up = NULL;
                             free(aux); 
                             aux = NULL;
                       }
                 }   
                 else
                 {
                       printf("\n The i integer does not exist \n");
                 }           
     }
     else if(((*h) != NULL)&&((*h)->down == NULL))
     {
                 if((*h)->da_i == da)
                 {
                       free(*h);
                       (*h) = NULL;
                 }   
                 else
                 {
                       printf("\n The i integer does not exist \n");
                 }                                                      
     }
     else if((*h) == NULL)
     {
                 printf("\n The column's head is NULL, so the i integer does not exist \n");
     }
}

void print_rows(tp h) 
{
        if (h->da_j != 0)
        {
               printf(" (%d,%d) ",h->da_i, h->da_j);
        }
        if(h->next != NULL)
        {
               print_rows(h->next);
        }
}

void print_columns(tp h) 
{
        if (h->da_i != 0)
        {
               printf(" (%d,%d) ",h->da_i, h->da_j);
        }
        if(h->down != NULL)
        {
               print_columns(h->down);
        }
}

// # of edges in sparse array
int number_of_edges()
{
	int count = 0;

	for (int k = 1; k < MAX; k++ )
        {
                h = column[k];
                
		if (h->next != NULL)
                {
                   while(h->next != NULL)
                   {
			count += 1;
                        h = h->next;
                   }
		}
	}
	printf(" The number of Edges in the Sparse Array is: %d \n",count);
	return count;
}

// # of vertices in sparse array
int number_of_vertices()
{
	int count = 0;

	for (int k = 1; k < MAX; k++ )
        {
                h = column[k];
                
		if (h->next != NULL)
                {
	            count += 1;
		}
	}
	printf("\n The number of Vertices in the Sparse Array is: %d \n",count);
	return count;
}

// create a spanning tree
void spanning_tree(tp *h)
{
      tp aux,aux1,aux2,aux3;
      int lvl = 0;
      aux = *h;
  
      while (aux->next != NULL)
      {
        aux = aux->next;

        if ((aux->active != TRUE) && (aux->da_i != aux->da_j))
        {
             aux->active = TRUE;
             column[aux->da_j]->level = lvl+1;
             column[aux->da_j]->in = TRUE;

             column[aux->da_j]->father = column[root];

             aux1 = (column[aux->da_j])->next;
             while (aux1 != NULL)
             {
                if ((aux1->da_j == aux->da_i) && (aux1->da_i == aux->da_j)) //((aux1->active != TRUE) && 
                {
                   aux1->active = TRUE;
                }
                aux1 = aux1->next;
              }
           }  
        } 

        for (lvl = 1; lvl < MAX; lvl++)
        {
           for (int k = 1; k < MAX; k++)
           {
              if (column[k]->level == lvl)
              {

                if (column[k]->next != NULL)
                {
                    aux2 = column[k]->next;
 
                    while (aux2 != NULL)
                    {
                        if ((aux2->active != TRUE) && (aux2->da_i != aux2->da_j) && (column[aux2->da_j]->in != TRUE))
                        {
                             aux2->active = TRUE;
                             column[aux2->da_j]->level = lvl+1;
                             column[aux2->da_j]->in = TRUE;

                             column[aux2->da_j]->father = column[aux2->da_i];

                             aux3 = (column[aux2->da_j])->next;
                             while (aux3 != NULL)
                             {
                                    if ((aux3->active != TRUE) && ((aux3->da_j == aux2->da_i) && (aux3->da_i == aux2->da_j)))
                                    {
                                           aux3->active = TRUE;
                                    }
		                    aux3 = aux3->next;
                             }
		         }  
         	         aux2 = aux2->next;
                       }
                    }
                }
           }
       } 
       for (int p = 1; p < MAX; p++)
       {
         if (column[p]->level != -1)
         {
           printf(" row:%d -> level:%d \n", p, column[p]->level);
         }
       }
}

// delete spanning tree
void delete_spanning_tree()
{
   tp aux;
   if (exists == TRUE) 
   {
       for (int k = 1; k < MAX; k++)
       {
           aux = column[k];
           aux->level = -1;
           aux->in = FALSE;

           if (aux->next != NULL)
           {
             while (aux->next != NULL)
             {
               aux = aux->next;
               aux->active = FALSE;
             }
           }
       }
   }
   else
   { 
       printf("\n Spanning Tree doesn't exist! \n");
   }
}

// print the active adges
void print_active_edges(tp h) 
{
     if(h != NULL)
     {
           if(h->active == TRUE)
           {
              printf("active: (%d,%d) ",h->da_i, h->da_j);
              
           }
           print_active_edges(h->next);
     }
}

void print_inactive_edges(tp h) 
{
     if(h != NULL)
     {
           if((h->active != TRUE) && (h->da_j != 0))
           {
              printf(" inactive: (%d,%d) ",h->da_i, h->da_j);
              
           }
           print_inactive_edges(h->next);
     }
}

// print the spanning tree
void print_spanning_tree() 
{
   int m = 0;
   if (exists == TRUE)
   {
     for (int lvl = 0; lvl < MAX; lvl++)
     {
         for (int k = 1; k < MAX; k++)
         {
             if (column[k]->level == lvl)
             {
                 if (column[k]->in == TRUE)
                 {
                     printf("\n level: %d, node: %d, parent: %d", column[k]->level,column[k]->da_i,column[k]->father->da_i);
                     m = 1;
                 }
              } 
          }
          if (m == 1)
          {
              printf("\n");
              m = 0;
          }
      }
   }
   else
   { 
       printf("\n Spanning Tree doesn't exist! \n");
   }
}

/* void find_circles()
{
  tp aux, aux2, aux3;
  
  if (exists == TRUE)
  {
     for(int k = 1; k < MAX; k++)
     {
        if (column[k]->next != NULL)
        {
            aux = column[k]->next;
 
            while (aux != NULL)
            {
	 	if ((aux->active != TRUE) && (aux->da_j !=0))
                {
			printf("\n Inactive Edge: (%d,%d) \n", aux->da_i, aux->da_j);
                        printf("\n Paths to Root: \n");
                        printf("\n");

                        int i = 0, j = 0, m = 0, n = 0, same = 0;
	                int path_i[MAX-1]; 
                        int path_j[MAX-1];
	                for (i=0; i < MAX-1; ++i)
                        {
		             if (path_i[i] != 0)
                             {
			            path_i[i] = 0;
                             }
		             if (path_j[i] != 0)
                             {
			            path_j[i] = 0;
                             }
	                } 

                        aux2 = column[aux->da_i];
	                i = 0; 
                        while (aux2 != column[root])
                        {	    
                             path_i[i] = aux2->da_i;		
		             aux2 = aux2->father; 
		             ++i;
                        }
                        path_i[i] = root;
	                for (n = i; n >= 0; n--)
                        {
		             printf(" %d \n", path_i[n]);
                             if (n != 0)
                             {
                                 printf(" ↑ \n");
                             }
                        }
                        printf("\n");
 
                        aux3 = column[aux->da_j];
	                j = 0;
                        while (aux3 != column[root])
                        { 
                             path_j[j] = aux3->da_i;
		             aux3 = aux3->father;
		             ++j;
	                }
                        path_j[j] = root;
                        printf("\n");
                        for (m = j; m >= 0; m--)
                        {
		             printf(" %d \n", path_j[m]);
                             if (m != 0)
                             {
                                 printf(" ↑ \n");
                             }
                        }
                        
	                for (m = 0; m <= i; ++m)
                        {
		             for (n = 0; n <= j; ++n)
                             {
			           if (path_i[m] == path_j[n])
                                   {
				            same = same+1;
			           }
		             }
	                }
                        
                        //printf("\n j: %d \n", j);
                        j = j - same + 1;
                        //printf("\n j: %d \n", j);
	                printf("\n Vertices of Cyrcle: {");
	                for (n = 0; n <= j; ++n)
                        {
		             printf(" %d", path_j[n]);
                             printf(",");
                        }
	                for (i = (i-same); i >= 0; --i) 
                        {
		             printf(" %d", path_i[i]);
                             if (i != 0)
                             { 
                                 printf(",");
                             }
                        }
	                printf(" } \n"); 
                  } 
                  aux =  aux->next;
               }
           }
       }
   }
   else
   { 
       printf("\n Spanning Tree doesn't exist! \n");
   }
} */

void find_circles()
{
  tp aux, aux2, aux3, aux4, aux5;
  
  if (exists == TRUE)
  {
     for(int k = 1; k < MAX; k++)
     {
        if (column[k]->next != NULL)
        {
            aux = column[k]->next;
 
            while (aux != NULL)
            {
	 	if ((aux->active != TRUE) && (aux->da_j !=0))
                {
			printf("\n Inactive Edge: (%d,%d)", aux->da_i, aux->da_j);
                        printf("\n Paths to Root: \n");

                        int i = 0, j = 0, same = 0;

	                tp header_path_i = NULL; 
                        tp header_path_j = NULL;
                        
                        aux2 = column[aux->da_i];
                        while (aux2 != column[root])
                        {	
                             tempp = (tp)malloc(sizeof(struct tf));
                             tempp->da_i = aux2->da_i;
                             tempp->next = NULL; tempp->previous = NULL; tempp->up = NULL; tempp->down = NULL; tempp->da_j = 0;
                             insert_queue_path(&(header_path_i),tempp); 
		             aux2 = aux2->father; 
                             ++i;
                        }	
                        tempp = (tp)malloc(sizeof(struct tf));
                        tempp->da_i = aux2->da_i;
                        tempp->next = NULL; tempp->previous = NULL; tempp->up = NULL; tempp->down = NULL; tempp->da_j = 0;
                        insert_queue_path(&(header_path_i),tempp); 

                        printf("\n");
                        print_queue(header_path_i);
 
                        aux3 = column[aux->da_j];
                        while (aux3 != column[root])
                        {	
                             tempp = (tp)malloc(sizeof(struct tf));
                             tempp->da_i = aux3->da_i;
                             tempp->next = NULL; tempp->previous = NULL; tempp->up = NULL; tempp->down = NULL; tempp->da_j = 0;
                             insert_queue_path(&(header_path_j),tempp); 
		             aux3 = aux3->father; 
                             j++;
                        }
                        tempp = (tp)malloc(sizeof(struct tf));
                        tempp->da_i = aux3->da_i;
                        tempp->next = NULL; tempp->previous = NULL; tempp->up = NULL; tempp->down = NULL; tempp->da_j = 0;
                        insert_queue_path(&(header_path_j),tempp); 

                        printf("\n");
                        print_queue(header_path_j);

                        aux4 = header_path_i;
                        aux5 = header_path_j;
                        while (aux4 != NULL) 
                        {
                             while (aux5 != NULL)
                             {
                                    if (aux4->da_i == aux5->da_i)
                                    {
                                           same = same+1;
                                    }                   
                                    aux5 = aux5->next;
                             }
                             aux5 = header_path_j;
                             aux4 = aux4->next;
                        }

                        aux4 = header_path_i;
                        aux5 = header_path_j;
                        j = j - same + 1;

	                printf("\n Vertices of Cyrcle: {");
	                for (int n = 0; n <= j; ++n)
                        {
		             printf(" %d", aux5->da_i);
                             printf(",");
                             aux5 = aux5->next;
                        }
	                for (int n = (i-same); n >= 0; --n) 
                        {
                             aux4 = aux4->next;
                        }
                        for (i = (i-same); i >= 0; --i) 
                        {   
		             printf(" %d", aux4->previous->da_i);
                             aux4 = aux4->previous;
                             if (i != 0)
                             { 
                                 printf(",");
                             }
                        }
	                printf(" } \n");
 
                        delete_queue_path(&header_path_i);
                        delete_queue_path(&header_path_j);

                        printf("\n Circle found! Do you wish to find the next cirlce? \n");
                        printf("\n Please press 'Y' if you want to 'CONTINUE' \n");
                        printf("\n ");
                        char ch='a';
                        fflush(stdin);
                        scanf("%c",&ch);
                        getchar();
                        switch(ch)
                        {
                             case 'Y':
                             {
                                 break; 
                             }
                             default:
                             {
                                 printf("\n EXIT \n");
                                 return;
                             }
                        }

                  }
                  aux =  aux->next;
               }
           }  
       }
   }
   else
   { 
       printf("\n Spanning Tree doesn't exist! \n");
   }
}

void insert_queue_path(tp *header,tp too)
{
   tp aux;
   if((*header) != NULL) 
   {
         if(((*header)->next) != NULL)
         {                 
             aux = (*header);
             insert_queue_path(&(aux->next),too);
         }
         else
         {
             too->previous = (*header);
             too->next = NULL;
             (*header)->next = too;
         }
    }
    else
    {
         (*header) = too;
         (*header)->next = NULL;
         (*header)->previous = NULL;
    } 
} 

void delete_queue_path(tp *header)
{
   tp aux, next;
   aux = *header;
   while (aux != NULL)
   {
         next = aux->next;
         free(aux); 
         aux = next;
   }
   (*header) = NULL; 
} 

void print_queue(tp header) 
{
     tp aux;
     if(header != NULL)
     {
          aux = header; 
          while(aux->next != NULL)
          {
                aux = aux->next;
          }
          while(aux != NULL)
          {
                printf(" %d \n",aux->da_i);
                if(aux->previous != NULL)
                {
                     printf(" ↑ \n");
                }
                aux = aux->previous;
          }
     }
     else
     {
          printf("\n The head is NULL \n");
     }
}
