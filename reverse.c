#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include<sys/stat.h>
#include<unistd.h>

typedef struct Node
{
    char *data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct LinkList
{
    Node *head;
    Node *tail;
    Node *cur;
    int size;
} LinkList;

LinkList *create()
{
    LinkList *list = (LinkList *)malloc(sizeof(LinkList));
    list->head = (Node *)malloc(sizeof(Node));
    if (list->head == NULL)
    {
        printf("memory allocate errot \n");
        exit(-1);
    }
    // Tail Pointer Initialization
    list->tail = list->head;
    list->tail->next = NULL;
    // Read head-Pointer data
    //     list->head->data = (char*)malloc(10*sizeof(char));
    //     scanf("%s",list->head->data);
    // Allocate memory
    list->cur = (Node *)malloc(sizeof(Node));
    list->cur->data = (char *)malloc(10 * sizeof(char));
    return list;
}

int main(int argc, char **argv)
{
    LinkList *list = create();
    if (argc == 1)
    {
        // Enter EOF to terminate
        while (scanf("%s", list->cur->data) != EOF)
        {
            // connected to the end of linklist
            list->tail->next = list->cur;
            list->cur->prev = list->tail;
            list->tail = list->cur;
            // Allocate memory
            list->cur = (Node *)malloc(sizeof(Node));
            list->cur->data = (char *)malloc(10 * sizeof(char));
        }
        // Traveral output
        list->tail->next = NULL;
        list->cur = list->tail;
        while (list->cur != list->head)
        {
            printf("%s\n", list->cur->data);
            list->cur = list->cur->prev;
        }
    }
    else if (argc == 2)
    {
        char *fileName = argv[1];
        FILE *fp = fopen(fileName, "r");
        if (fp == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '/no/such/file.txt'\n");
            exit(1);
        }
        // Temporary storge and handling
        char temp[10];
        while (fgets(temp, 10, fp) != NULL)
        {
            // Filter trailing line breaks
            if (temp[strlen(temp) - 1] == '\n')
                strcpy(temp + strlen(temp) - 1, "\0");
            strcpy(list->cur->data, temp);

            list->tail->next = list->cur;
            list->cur->prev = list->tail;
            list->tail = list->cur;
            // Allocate memory
            list->cur = (Node *)malloc(sizeof(Node));
            list->cur->data = (char *)malloc(10 * sizeof(char));
        }
        // Traversal output
        list->tail->next = NULL;
        list->cur = list->tail;
        //        printf("%s\n", list->cur->data);
        //        list->cur = list->cur->prev;
        while (list->cur != list->head)
        {
            printf("%s\n", list->cur->data);
            list->cur = list->cur->prev;
        }
        fclose(fp);
    }
    else if (argc == 3)
    {
        char *inputFile = argv[1];
        char *ouputFile = argv[2];
        if (strcmp(argv[1], argv[2]) == 0)
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        struct stat file1,file2;
        stat(inputFile, &file1);
        stat(ouputFile, &file2);
        if(file1.st_ino == file2.st_ino)
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        FILE *fin = fopen(inputFile, "r");
        FILE *fout = fopen(ouputFile, "w");
        if (fin == NULL || fout == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '/no/such/file.txt'\n");
            exit(1);
        }

        char temp[10];
        while (fgets(temp, 10, fin) != NULL)
        {
            // Filter trailing line breaks
            if (temp[strlen(temp) - 1] == '\n')
                strcpy(temp + strlen(temp) - 1, "\0");
            strcpy(list->cur->data, temp);

            list->tail->next = list->cur;
            list->cur->prev = list->tail;
            list->tail = list->cur;
            // Allocate memory
            list->cur = (Node *)malloc(sizeof(Node));
            list->cur->data = (char *)malloc(10 * sizeof(char));
        }

        list->tail->next = NULL;
        list->cur = list->tail;
        //		fprintf(fout,list->cur->data);
        //		fprintf(fout,"\n");
        //        list->cur = list->cur->prev;
        while (1)
        {
            // printf("%s", list->cur->data);
            fprintf(fout, "%s", list->cur->data);
            list->cur = list->cur->prev;
            if (list->cur != list->head)
            {
                fprintf(fout, "\n");
            }
            else
            {
                break;
            }
        }
        fprintf(fout, "\n");
        fclose(fin);
        fclose(fout);
    }
    else
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    return 0;
}