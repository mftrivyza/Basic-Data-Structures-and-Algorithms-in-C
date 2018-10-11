#include <stdio.h>
#include <stdlib.h>

typedef struct treenode *ptn;
struct treenode
{
       int key;
       ptn left, right;
};

ptn Search(ptn root, int data);
void Insert(ptn *root, int data);
void Delete(ptn *root, int data);
void Print(ptn *root);

int main(void)
{
    char fry,fry2;
    fry='a';
    
    int data;
    ptn root;
    root=NULL;
    
    while(fry!='q')
    {
                   printf("\n Previous Fry: %c \n",fry);
                   if(fry!='q')
                   {
                               printf("\n Give a new choice: \n");
                               printf("\n (i to 'Insert', s to 'Search', d to 'Delete', p to 'Print_Sorted', q to 'Quit') \n");
                               
                               fry='a';
                               fflush(stdin);
                               fry=getchar();
                               
                               if(fry=='q')
                               {
                                           printf("\n QUIT. \n");
                               }
                               if(fry=='i')
                               {
                                           printf("\n INSERT NODE KEY (int): \n");
                                           printf("\n ");
                                           scanf("%d", &data);
                                           getchar();
                                           Insert(&root, data);         
                               }
                               if(fry=='s')
                               {
                                           printf("\n SEARCH TREE \n");
                                           printf("\n Insert a Node Key (int) to check if it already exists in Tree: \n");
                                           printf("\n ");
                                           scanf("%d", &data);
                                           getchar();
                                           Search(root, data);   
                               }
                               if(fry=='d')
                               {
                                          printf("\n DELETE NODE KEY (int):\n"); 
                                          printf("\n ");
                                          scanf("%d", &data);
                                          getchar();
                                          Delete(&root, data);         
                               }            
                               if(fry=='p')
                               {
                                           printf("\n PRINT SORTED TREE: \n");
                                           printf("\n ");
                                           Print(&root);                     
                               }
                   }
    }
    system ("pause");
    return 0;
} 

void Insert(ptn *root, int data)
{
     if((*root) != NULL)
     {
              if( data < (*root)->key )
              {
                      Insert( &((*root)->left), data );
              }
              else
              {
                      if( data > (*root)->key )
                      {
                              Insert( &((*root)->right), data );
                      }
                      else
                      {
                              printf("\n Data already exists in Tree. \n");
                      }
              }  
     }
     else
     {
               *root=(ptn)malloc(sizeof(struct treenode));
               (*root)->key = data;
               (*root)->left = NULL;
               (*root)->right = NULL;
     }
}

ptn Search(ptn root, int data)
{
   if (root != NULL)
   {
            if(root-> key == data)
            {
                      printf("\n The data exists in Tree. \n");
                      return root;
            }
            if(data < root->key)
            {
                    if(root-> left != NULL)
                    {
                              return Search(root->left, data);
                    }
                    else
                    {
                              printf("\n The data does not exist in Tree. \n");
                              return NULL; 
                    }
            }
            if(data > root->key)
            {
                    if(root-> right != NULL)
                    {
                              return Search(root->right, data);
                    }
                    else
                    {
                              printf("\n The data does not exist in Tree. \n");
                              return NULL;
                    }
            }
   }
   if(root == NULL)
   {
           printf("\n The Tree is empty. \n");
           return NULL;
   }
}

void Delete(ptn *root, int data)
{
    ptn temp, next;
    
    if ((*root) != NULL)
    {
             if(data == (*root)->key)
             {
                     if( (*root)->left == NULL && (*root)->right != NULL )
                     {
                                      temp = (*root);
                                      (*root) = (*root)->right;
                                      free(temp);
                                      temp=NULL;
                     }
                     else if( (*root)->right == NULL && (*root)->left != NULL )
                     {
                                       temp = (*root);
                                       (*root) = (*root)->left;
                                       free(temp);
                                       temp=NULL;
                     }
                     
                     else if( (*root)->left != NULL && (*root)->right != NULL )
                     {
                                      next = (*root)->right;
                                      while(next->left != NULL)
                                      {
                                                next = next->left;
                                      }
                                      
                                      (*root)->key = next->key;
                                      
                                      Delete( &((*root)->right),(*root)->key );
                     }
                     else
                     {
                                      (*root) = NULL;
                     }
             }
             else if(data < (*root)->key)
             {
                     if( (*root)->left != NULL)
                     {
                         Delete(&((*root)->left),data);
                     }
                     else
                     {
                         printf("\n The data does not exist in Tree. \n");
                     }
                     
             }
             else if(data > (*root)->key)
             {
                     if( (*root)->right != NULL)
                     {
                         Delete(&((*root)->right),data);
                     }
                     else
                     {
                         printf("\n The data does not exist in Tree. \n");
                     }   
             }
     }
     else
     {
             printf("\n The Tree is emprty. \n");
     }
}

void Print(ptn *root) 
{
     if((*root) != NULL)
     {
              if( ((*root)->left) != NULL )
              {
                            Print( &((*root)->left) );
                            
              }
              
              printf("%d\n ",(*root)->key);
                            
              if( ((*root)->right) != NULL )
              {
                            
                            Print( &((*root)->right) );
              }
     }
     else
     {
              printf("\n The Tree is emprty. \n");
     }
}
