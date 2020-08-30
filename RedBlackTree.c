#include <stdio.h>
#include <stdlib.h>

typedef struct RBTnode *ptn;
struct RBTnode
{
       int key;
       char color;
       ptn left;
       ptn right;
       ptn parent;
};

ptn root; //= NULL;

void RBTInsert(int data, ptn nil);
void RBTInsertFix(ptn z, ptn nil);
void LeftRotate(ptn x, ptn nil);
void RightRotate(ptn y, ptn nil);
ptn RBTSearch(ptn root, ptn nil, int data);
void RBTDelete(ptn z, ptn nil);
ptn TREE_MINIMUM(ptn x, ptn nil);
void RBTransplant(ptn u, ptn v, ptn nil);
void RBTDeleteFix(ptn x, ptn nil);
void InOrderTraversal(ptn root, ptn nil); 

int main(void)
{
    char fry,fry2;
    fry='a';
    
    int data;
    ptn nil = (ptn)malloc(sizeof(struct RBTnode));
    nil->color = 'b';
    root = nil;
    root->left = nil;
    root->right = nil;
    root->parent = nil;
    
    while(fry!='q')
    {
                   printf("\n Previous Fry: %c \n",fry);
                   if(fry!='q')
                   {
                               printf("\n Give a new choice: \n");
                               printf("\n (i to 'Insert', s to 'Search', d to 'Delete', p to 'Print_Sorted', q to 'Quit') \n ");
                               
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
                                           scanf("%d",&data);
                                           getchar();
                                           RBTInsert(data,nil);  
                                           printf("\n");      
                               }
                               if(fry=='s')
                               {
                                           printf("\n SEARCH TREE \n");
                                           if(root == nil)
                                           {
                                                   printf("\n The Tree is emprty. \n");
                                           }
                                           else
                                           {
                                               printf("\n Insert a Node Key (int) to check if it already exists in Tree: \n");
                                               printf("\n ");
                                               scanf("%d", &data);
                                               getchar();
                                               RBTSearch(root, nil, data);   
                                           }
                               }
                               if(fry=='d')
                               {
                                          if(root == nil)
                                          {
                                                   printf("\n The Tree is emprty. \n");
                                          }
                                          else 
                                          {
                                               printf("\n DELETE NODE KEY (int):\n "); 
                                               printf("\n ");
                                               scanf("%d", &data);
                                               getchar();
                                               ptn z = RBTSearch(root, nil, data);
                                               //printf(" node's elements: %d-%c\n", z->key, z->color);
                                               RBTDelete(z, nil);
                                               printf("\n");
                                          }      
                               }            
                               if(fry=='p')
                               {
                                           printf("\n PRINT SORTED TREE: \n ");
                                           if(root == nil)
                                           {
                                                   printf("\n The Tree is emprty. \n");
                                           }
                                           else
                                           {
                                               printf("\n");
                                               InOrderTraversal(root,nil);
                                               printf("\n"); 
                                           }                
                               }
                   }
    }
    system ("pause");
    return 0;
} 

void RBTInsert(int data, ptn nil)
{
     ptn z = (ptn)malloc(sizeof(struct RBTnode));
     z->key = data;
     z->left = nil;
     z->right = nil;
     z->color = 'r';
     ptn x = root;
     ptn y;
     
     if (root == nil)
     {
          root = z;
          root->color = 'b';
          return;
     }
     
     while (x != nil)
     {
           y = x;
           if (z->key < x->key)
           {
                x = x->left;
           }
           else if (z->key > x->key)
           {
                x = x->right;
           }
           else
           {
               printf("\n Data already exists in Tree. \n");
               return;
           }
     }
     z->parent = y;
     if (y == nil)
     {
          root = z;
     }
     else if(z->key < y->key)
     {
          y->left = z;
     }
     else 
     {
          y->right = z;
     }
     
     RBTInsertFix(z,nil);
     return;
}

void RBTInsertFix(ptn z, ptn nil)
{
     ptn y;
     root->parent = nil;
     
     while (z != root && z->parent->color == 'r')
     //while (z->parent->color == 'r')
     {
           if (z->parent == z->parent->parent->left)
           {
                         y = z->parent->parent->right;
                         if (y->color == 'r')
                         {
                                      z->parent->color = 'b';
                                      y->color = 'b';
                                      z->parent->parent->color = 'r';
                                      z = z->parent->parent;
                                      //root->color = 'b';
                                      //return;
                                      
                         }
                         else 
                         {
                              if (z == z->parent->right)
                              {
                                    z = z->parent;
                                    LeftRotate(z,nil);
                              }
                              z->parent->color = 'b';
                              z->parent->parent->color = 'r';
                              RightRotate(z->parent->parent, nil);
                              
                              //root->color = 'b';
                              //return;
                         }
           }
           else 
           {
                y = z->parent->parent->left;
                if (y->color == 'r')
                {
                             z->parent->color = 'b';
                             y->color = 'b';
                             z->parent->parent->color = 'r';
                             z = z->parent->parent;
                             
                             //root->color = 'b';
                             //return;
                }
                else 
                {
                     if (z == z->parent->left)
                     {
                           z = z->parent;
                           RightRotate(z,nil);
                     }
                     z->parent->color = 'b';
                     z->parent->parent->color = 'r';
                     LeftRotate(z->parent->parent, nil);
                     
                     //root->color = 'b';
                     //return;
                }
           }
     }
     root->color = 'b';
}

void LeftRotate(ptn x, ptn nil)
{
     root->parent = nil;
     ptn y;
     
     y = x->right;  
     x->right = y->left; 
     if(y->left != nil)
     {
         y->left->parent = x; 
     }
     y->parent = x->parent; 
     if(x->parent == nil)
     {
         root = y;
     }
     else if(x == x->parent->left)
     {
          x->parent->left = y;
     }
     else 
     {
          x->parent->right = y;
     }
     y->left = x; 
     x->parent = y;
     return;
}

void RightRotate(ptn y, ptn nil)
{
     root->parent = nil;
     ptn x;
     
     x = y->left; 
     y->left = x->right; 
     if (nil != x->right)
     {
          x->right->parent = y;
     }
     x->parent = y->parent; 
     if( y->parent == nil)
     {
         root = x;
     } 
     else if( y == y->parent->right)
     {
          y->parent->right = x; 
     }
     else 
     {
          y->parent->left = x;
     }
     x->right = y; 
     y->parent = x; 
     return;
}

ptn RBTSearch(ptn root, ptn nil, int data)
{
   ptn z = (ptn)malloc(sizeof(struct RBTnode));
   z->key = data;
   z->left = nil;
   z->right = nil;
   z->color = 'r';
   ptn x = root;
   ptn y;
   
   while (x != nil)
   {
            y = x;
            if(x-> key == z->key)
            {
                      printf("\n The data exists in Tree (and you can delete it). \n");
                      return x;
            }
            if (z->key < x->key)
            {
                    if(x-> left != nil)
                    {
                              return RBTSearch(x->left,nil, data);
                    }
                    else
                    {
                              printf("\n The data does not exist in Tree. \n"); 
                              return nil;
                    }
            } 
            if(z->key > x->key)
            {
                    if(x-> right != nil)
                    {
                              return RBTSearch(x->right,nil, data);
                    }
                    else
                    {
                              printf("\n The data does not exist in Tree. \n");
                              return nil;
                    }
            }
   }
}

void RBTDelete(ptn z, ptn nil)
{
     ptn y, x;
     char y_original_color;
     y = z;
     y_original_color = y->color;
     
     if (z->left == nil)
     {
                 x = z->right;
                 RBTransplant(z, z->right, nil);
     }
     else if (z->right == nil)
     {
          x = z->left;
          RBTransplant(z, z->left, nil);
     }
     else 
     {
          y = TREE_MINIMUM(z->right, nil);
          y_original_color = y->color;
          x = y->right;
          if (y->parent == z)
          {
                   x->parent = y;
          }
          else 
          {
               RBTransplant(y, y->right, nil);
               y->right = z->right;
               y->right->parent = y;
          }
          RBTransplant(z, y, nil);
          y->left = z->left;
          y->left->parent = y;
          y->color = z->color;
          
          free(z);
          //free(y);
          z = nil;
          //y = nil;
     }
     if (y_original_color == 'b')
     {
                         RBTDeleteFix(x, nil);
     }
}

void RBTDeleteFix(ptn x, ptn nil)
{
     ptn w;
     
     while ((x != nil) && (x->color == 'b'))
     {
           if (x == x->parent->left)
           {
                 w = x->parent->right;
                 if (w->color == 'r')
                 {
                              w->color = 'b';
                              x->parent->color = 'r';
                              LeftRotate(x->parent, nil);
                              w = x->parent->right;
                 }
                 if ((w->left->color == 'b') && (w->right->color == 'b'))
                 {
                                     w->color = 'r';
                                     x = x->parent;
                 }
                 else 
                 {
                      if (w->right->color == 'b')
                      {
                                          w->left->color = 'b';
                                          w->color = 'r';
                                          RightRotate(w, nil);
                                          w = x->parent->right;
                      }
                      w->color = x->parent->color;
                      x->parent->color = 'b';
                      w->right->color = 'b';
                      LeftRotate(x->parent, nil);
                      x = root;
                 }
           }
           else
           {
                 w = x->parent->left;
                 if (w->color == 'r')
                 {
                              w->color = 'b';
                              x->parent->color = 'r';
                              RightRotate(x->parent, nil);
                              w = x->parent->left;
                 }
                 if ((w->right->color == 'b') && (w->left->color == 'b'))
                 {
                                     w->color = 'r';
                                     x = x->parent;
                 }
                 else 
                 {
                      if (w->left->color == 'b')
                      {
                                         w->right->color = 'b';
                                         w->color = 'r';
                                         LeftRotate(w, nil);
                                         w = x->parent->left;
                      }
                      w->color = x->parent->color;
                      x->parent->color = 'b';
                      w->right->color = 'b';
                      RightRotate(x->parent, nil);
                      x = root;
                 }
           }
     }
     x->color = 'b';
}

ptn TREE_MINIMUM(ptn x, ptn nil)
{
     while (x->left != nil)
     {
           x = x->left;
     }
     return x;
}

void RBTransplant(ptn u, ptn v, ptn nil)
{
     root->parent = nil;
     
     if (u->parent == nil)
     {
          root = v;
     }
     else if (u == u->parent->left)
     {
          u->parent->left = v;
     }
     else 
     {
          u->parent->right = v;
     }
     
     v->parent = u->parent;
}        
     
void InOrderTraversal(ptn root, ptn nil)
{
     ptn temp = root;
     if (temp != nil)
     {
              InOrderTraversal(temp->left, nil);
              printf(" %d-%c\n", temp->key, temp->color);
              InOrderTraversal(temp->right, nil);
     }
     return;
}
