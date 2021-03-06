#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
//#include <cstdlib>
#define MAX 20

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
    printf("%d ", arr[i]);
    printf("\n");
}
void swap(int *a, int *b) {
    int t;
    t=*a; *a=*b; *b=t;
}
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++)
    for (j = 0; j < n-i-1; j++)
    if (arr[j] > arr[j+1])
    swap(&arr[j], &arr[j+1]);
}
void heapify(int arr[], int n, int i) {
    int largest = i; 
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i=n-1; i>0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int process_id, size, array[30], i, choice, search, temp[20];
    char str[30];
    char *arg[30];
    
    printf("\nENTER SIZE OF ARRAY : ");
    scanf("%d", &size);
    
    printf("\nENTER ARRAY ELEMENTS : ");
    for(i=0; i<size; i++)
        scanf("%d", &array[i]);
    
    printf("\nENTER ELEMENT TO BE SEARCHED : ");
    scanf("%d", &search);
    //bubbleSort(array, size);
    
    printf("\nMENU : \n1)HEAP SORT\n2)BUBBLE SORT\nENTER YOUR CHOICE : ");
    scanf("%d", &choice);

    switch(choice) {
        case 1 : 
            printf("\nHEAP SORT (PARENT)");
            heapSort(array, size);
            break;
        case 2 : 
            printf("\nBUBBLE SORT (PARENT)");
            bubbleSort(array, size);
            break;
    }

    printf("\nFORK DONE\n");
    process_id = fork();

    switch(process_id) {
        case -1 : 
            printf("\n\tERROR!");
            break;

        case 0 : 
            sleep(1); 
            printf("\n\n\t===========CHILD BLOCK=============");
            printf("\n\tCHILD ID : %d", getpid());
            printf("\n\tPARENT ID : %d", getppid());

            printf("\n\tSORTED ARRAY (CHILD) : ");
            printArray(array, size);
            
            for(i=0; i<size; i++)
                temp[i] = array[i];

            temp[i] = search;
            for(i=0; i<size+1; i++) {
                sprintf(str, "%d", temp[i]);
                arg[i] = malloc(sizeof(str));
                strcpy(arg[i], str);
            }
            arg[i]=NULL;
            execv("./bsearch", arg);
            printf("Exec function Fail: Will not print this line if exec fuctions worked properly");
            break;
        
        default : 
            printf("\n\n\t===========PARENT BLOCK=============");
            printf("\n\tPARENT ID : %d", getpid());

            printf("\n\tSORTED ARRAY(PARENT) : ");
            printArray(array, size);

            printf("\nWaited for %d child process to get finished..\n", wait(NULL));

            break;
    }
    return 0;
}

/*

ENTER SIZE OF ARRAY : 5

ENTER ARRAY ELEMENTS : 1 8 3 7 4

ENTER ELEMENT TO BE SEARCHED : 3

MENU : 
1)HEAP SORT
2)BUBBLE SORT
ENTER YOUR CHOICE : 2

BUBBLE SORT (PARENT)
FORK DONE


	===========PARENT BLOCK=============
	PARENT ID : 18889
	SORTED ARRAY(PARENT) : 1 3 4 7 8 


	===========CHILD BLOCK=============
	CHILD ID : 18894
	PARENT ID : 18889
	SORTED ARRAY (CHILD) : 1 3 4 7 8 

No of arguments passed : 6
Arg[0] : 1
Arg[1] : 3
Arg[2] : 4
Arg[3] : 7
Arg[4] : 8
Arg[5] : 3
	ARGC : 6
Search : 3
	ELEMENT FOUND AT POSITION 1.

Waited for 18894 child process to get finished..

*/


/*

BASIC Function : exec, followed by combination of 4 letters that are l, e, v, p

1) l => pass parameters while calling function only
    e.g. 
    execl("/bin/ls", "ls", "-l", NULL);

2) v => pass vector/array of arguments instead of passing arguments directly in function
    e.g. 
    execv("/bin/ls", argv); 

3) e => pass envirnoment variables into the fucntions using sperate array/vector
    e.g.
    execve(const char *filename, char *const argv[ ], char *const envp[ ]);

4) p => p represents for path, use path variable to detect the current path of directory

*/