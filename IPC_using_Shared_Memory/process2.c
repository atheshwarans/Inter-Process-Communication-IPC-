//https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_shared_memory.htm
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
    printf("Process 2\n");

    char password[11],ch;

    int SharedMemID;
    key_t key;
    char *SharedMemPtr;

    key = ("process1",37);
    SharedMemID = shmget(key,50,IPC_CREAT | 0666);
    SharedMemPtr = shmat(SharedMemID, NULL, 0);

    //reading the password from the shared memory and writing into the variable password
    strcpy(password, SharedMemPtr);
    printf("The received password is : %s\n",password);
    
    int SpecialCharCount = 0, AlphaNumericCharCount = 0;
    int i = 0;
    ch = password[i];	
    while (ch != '\0')
    {
        if( (ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) )
        {
            AlphaNumericCharCount++;
        }
        else
        {
            SpecialCharCount++;
        }
        ch = password[++i];
    }   

    printf("The count of alphanumeric character sent is: %d\n", AlphaNumericCharCount);
    memcpy(SharedMemPtr + 11, &AlphaNumericCharCount ,sizeof(int));

    printf("The count of special characters sent is: %d\n", SpecialCharCount);
    
    //writing the alphanumeric and special character counts into shared memory
    memcpy(SharedMemPtr + 11 + sizeof(int), &SpecialCharCount, sizeof(int));
    pid_t PID = fork();
    if(PID == 0)
    {
        char *args[]={"./process3",NULL};
        execvp(args[0],args);
    }
    else
    {
        (void)waitpid(PID,NULL,0);
    }
}
