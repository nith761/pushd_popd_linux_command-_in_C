#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

typedef struct DNode
{
 char *d;
 struct DNode *next;
 } DNode;
 
 DNode *push(DNode *stack, const char *d)
 {
  DNode *node = (DNode *) malloc(sizeof(DNode));
  if(!node) {
  perror("malloc");
   exit(EXIT_FAILURE);
  }
  node->d = strdup(d);
  if(!node->d) {
  perror("strdup");
   exit(EXIT_FAILURE);
  }
  
  node->next =stack;
  return node;
  }
  
  DNode *pop (DNode *stack, char **d) {
   if (!stack) return NULL;
   DNode *next = stack->next;
   *d = stack->d;
   free(stack);
   return next;
   }
   
   int main (int argc , char *argv[]) {
   if (argc<2) {
      fprintf(stderr, "usage : %s <command> [dir]\n" , argv[0]);
      return EXIT_FAILURE;
      }
      
      static DNode *stack = NULL;
      char cwd[1024];
      
      if (strcmp(argv[1], "pushd") ==0) {
         if (argc<3) {
             fprintf(stderr, "Usage :%s pushd <dir>\n", argv[0]);
                   return EXIT_FAILURE;
                   }
                   
                   
     if (!getcwd(cwd, sizeof(cwd))) {
     	perror("getcwd");
     	return EXIT_FAILURE;
     	}
     	
     	
     if (chdir(argv[2])!= 0) {
         perror ("child");
         return EXIT_FAILURE;
         }
         
     stack = push(stack,cwd);
     printf("Directorg pushed :%s\n", cwd);
     
     }
        else if(strcmp(argv[1], "popd")==0){
        if(!stack) {
           fprintf(stderr,"Directory stack is empty\n");
           return EXIT_FAILURE;
           }
           
           char *d;
           stack =pop(stack , &d);
           
           if(chdir(d) !=0) {
           perror("chdir");
           return EXIT_FAILURE;
           }
           printf("Directory popped and changed to : %s\n" , d );
           free(d);
           }
           
           else {
           fprintf(stderr, "Unknown command :%s\n" , argv[1]);
           return EXIT_FAILURE;
           }
           return EXIT_SUCCESS;
  }
