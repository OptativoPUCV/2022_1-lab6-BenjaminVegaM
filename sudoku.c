#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i,j,p,num3[9] = {0};
  for(i=0 ; i<9 ; i++)
  {
    int num1[9] = {0};
    int num2[9] = {0};

    //recorrer en diagonal (i,i) y revisar filas y columnas a partir de ese punto
    for(j=0;j<9;j++)
    {
      printf("Verificando posicion [%i,%i] = %i\n",i,j,n->sudo[i][j]);
      //filas desde i,i
      if(n->sudo[i][j] != 0)
      {
        printf("Es diferente de 0\n");
        if(num1[n->sudo[i][j]] == 1)
        {
          return 0;
        }
        else
        {
          num1[n->sudo[i][j]] = 1;
        }
      }
      printf("Verificando posicion [%i,%i] = %i\n",j,i,n->sudo[j][i]);
      //columnas desde i,i
      if(n->sudo[j][i] != 0 && i != j)
      {
        printf("Es diferente de 0\n");
        if(num2[n->sudo[j][i]] == 1)
        {
          return 0;
        }
        else
        {
          num2[n->sudo[j][i]] = 1;
        }
      }      
    }
    //todas las submatrices
    for(p=0;p<9;p++)
    {
        i=3*(4/3) + (p/3) ;
        j=3*(4%3) + (p%3) ;
        printf("%d ",n->sudo[i][j]);
        if(p%3 == 2) printf("\n");
        if(num3[n->sudo[i][j]] == 1)
        {
          return 0;
        }
        else
        {
          num3[n->sudo[i][j]] = 1;
        }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n)
{
  printf("Creando Lista\n");
  List * list = createList();
  int i,j,k,isValid;
  for(i = 0 ; i < 9 ; i++)
  {
    printf("for i = %i\n", i);
    for(j = 0 ; j < 9 ; j++)
    {
      printf("for j = %i\n", j);
      printf("Casilla actual = %i\n", n->sudo[i][j]);
      if(n->sudo[i][j] == 0)
      {
        printf("Casilla vacia, agregando numero\n");
        for(k = 1 ; k < 10 ; k++)
        {
          n->sudo[i][j]=k;
          printf("Verificando numero K = %i en la posicion [%i,%i]\n",n->sudo[i][j],i,j);
          isValid = is_valid(n);
          printf("is_valid = %i\n", isValid);
          if(isValid == 1)
          {
            Node * adj = copy(n);
            pushBack(list, adj);
            if(adj->sudo != NULL)
            {
              printf("adj->sudo no es null\n");
            }
          }
        }
        n->sudo[i][j]=0;
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/