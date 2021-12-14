#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
void main()
{
    printf("Process 3\n");
    
    int AlphaNumericCharCount, SpecialCharCount;
    int SharedMemID;
    key_t key;
    char *SharedMemPtr;
    char Strength[7];

    key = ("process1",37);
    SharedMemID = shmget(key,50,IPC_CREAT | 0666);
    SharedMemPtr = shmat(SharedMemID, NULL, 0);

    AlphaNumericCharCount = *(SharedMemPtr + 11);
    printf("The count of alphanumeric character received is: %d\n", AlphaNumericCharCount);
    
    SpecialCharCount = *(SharedMemPtr + 11 + sizeof(int));
    printf("The count of special characters received is: %d\n", SpecialCharCount); 

    if (AlphaNumericCharCount >= SpecialCharCount)
    {
        strcpy(Strength,"Weak");
    }   
    else
    {
        strcpy(Strength,"Strong");
    }   
    
    printf("The strength of the password sent is: %s\n", Strength);
    strcpy(SharedMemPtr + 11 + 2 * sizeof(int),Strength);
    
}