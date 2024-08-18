#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

#define SIZE 100

typedef struct {
    char *dirs[SIZE];
    int T;
} DirStack;

void initStack(DirStack *stack) {
    stack->T = -1;
}


int isFull(DirStack *stack) {
    return stack->T == SIZE - 1;
}


int isEmpty(DirStack *stack) {
    return stack->T == -1;
}


void push(DirStack *stack, const char *dir) {
    if (isFull(stack)) {
        fprintf(stderr, "Error: Directory stack is full.\n");
        return;
    }
    char *dir_copy = strdup(dir);
    if (dir_copy == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }
    stack->dirs[++stack->T] = dir_copy;
}


char *pop(DirStack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Error: Directory stack is empty.\n");
        return NULL;
    }
    char *dir = stack->dirs[stack->T];
    stack->dirs[stack->T--] = NULL;
    return dir;
}


void pushd(DirStack *stack, const char *new_dir) {
    char current_dir[PATH_MAX];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("getcwd");
        return;
    }

    push(stack, current_dir);

    if (chdir(new_dir) != 0) {
        perror("chdir");
        char *dir = pop(stack); 
        free(dir);
    } else {
        printf("Changed directory to %s\n", new_dir);
    }
}


void popd(DirStack *stack) {
    char *dir = pop(stack);
    if (dir == NULL) {
        return;
    }

    if (chdir(dir) != 0) {
        perror("chdir");
    } else {
        printf("Changed directory to %s\n", dir);
    }

    free(dir);
}


void printUsage() {
    printf("Usage:\n");
    printf("  pushd <directory>\n");
    printf("  popd\n");
}

int main(int c, char *v[]) {
    DirStack stack;
    initStack(&stack);

    if (c < 2) {
        printUsage();
        return EXIT_FAILURE;
    }

    if (strcmp(v[1], "pushd") == 0) {
        if (c != 3) {
            printUsage();
            return EXIT_FAILURE;
        }
        pushd(&stack, v[2]);
    } else if (strcmp(v[1], "popd") == 0) {
        if (c != 2) {
            printUsage();
            return EXIT_FAILURE;
        }
        popd(&stack);
    } else {
        printUsage();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
