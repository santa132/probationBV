#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <regex.h>

#define BUFFER_SIZE 1024
#define MY_MQ "/mymq"
volatile bool receiveFlag = false;

struct Information
{
    char name[BUFFER_SIZE], phonenumber[13], imgpath[BUFFER_SIZE];
    unsigned char age;
};

bool checkValidPhoneNumber(char phonenumber[])
{
    regex_t regex;
    int value = regcomp(&regex, "[+84|84|0][1345789][0-9]{8}", REG_EXTENDED);
    if (value != 0)
    {
        printf("RegEx created failed.");
    }

    int result = regexec(&regex, phonenumber, 0, NULL, 0);
    if (result == 0)
        return true;
    return false;
}

int openFile(Information info)
{
    FILE *fp;
    char buffer[16];

    // open file to read
    fp = fopen(info.imgpath, "r");
    if (fp == NULL)
    {
        perror("Error");
        return (-1);
    }
    if (fgets(buffer, 16, fp) != NULL)
    {
        printf("Content of image file: ");
        // print on stdout
        puts(buffer);
    }
    fclose(fp);
    return 0;
}

void showInformation(Information info)
{
    printf("\n\nName: ");
    printf("%s\n", info.name);
    printf("Age: ");
    printf("%hhu\n", info.age);
    printf("Phone number: ");
    printf("%s\n", info.phonenumber);
    printf("Image file's path: ");
    printf("%s\n", info.imgpath);

    openFile(info);
}

void *sender(void *arg)
{
    mqd_t openSendMQ;
    int returnMQ;
    char buffer[BUFFER_SIZE];
    Information txInfo;

    openSendMQ = mq_open(MY_MQ, O_WRONLY | O_CREAT, 0666, NULL);
    if (openSendMQ == (mqd_t)-1)
    {
        printf("Open Message queue failed.\n");
    }
    else
    {
        while (1)
        {
            if (!receiveFlag)
            {
                // Enter information
                printf("\nEnter name: ");
                scanf("%s", txInfo.name);
                printf("Enter age: ");
                scanf("%hhu", &txInfo.age);
                printf("Enter phone number: ");
                scanf("%s", txInfo.phonenumber);
                printf("Enter file image's path: ");
                scanf("%s", txInfo.imgpath);

                // Save information to buffer
                strcat(buffer, txInfo.name);
                strcat(buffer, "\n"); // add endline to separate information
                // change format type  from unsigned char to char and append to buffer
                snprintf(buffer + strlen(buffer), BUFFER_SIZE - strlen(buffer), "%hhu", txInfo.age);
                strcat(buffer, "\n");
                strcat(buffer, txInfo.phonenumber);
                strcat(buffer, "\n");
                strcat(buffer, txInfo.imgpath);
                returnMQ = mq_send(openSendMQ, buffer, strlen(buffer) + 1, 0); // +1 to add '\0'
                if (returnMQ == -1)
                {
                    printf("Send message failed.\n");
                    break;
                }
                memset(buffer, 0, sizeof(buffer));
                receiveFlag = true;
            }
        }
    }
    mq_close(openSendMQ);
    return 0;
}

void *receiver(void *arg)
{
    mqd_t openReceiveMQ;
    int returnMQ, index = 0;
    char buffer[BUFFER_SIZE];
    openReceiveMQ = mq_open(MY_MQ, O_RDONLY, 0666, NULL);
    Information info;

    if (openReceiveMQ == (mqd_t)-1)
    {
        printf("Open Message queue failed.\n");
    }
    else
    {
        while (1)
        {   
            if (receiveFlag)
            {

                returnMQ = mq_receive(openReceiveMQ, buffer, sizeof(buffer)*1024, NULL);
                if (returnMQ == -1)
                {
                    printf("Receive failed");
                    break;
                }
                // printf("\nBuffer receive: %s\n", buffer);
                //  Token information from buffer received
                char *token = strtok(buffer, "\n");
                strcpy(info.name, token);
                token = strtok(NULL, "\n");
                info.age = (unsigned char)atoi(token);
                token = strtok(NULL, "\n");
                strcpy(info.phonenumber, token);
                token = strtok(NULL, "\n");
                strcpy(info.imgpath, token);

                // Check phone number
                if (checkValidPhoneNumber(info.phonenumber))
                {
                    showInformation(info);
                }
                else
                {
                    printf("Phone number wrong.\nPlease check valid phone number format.\n");
                }
                memset(buffer, 0, sizeof(buffer));
                receiveFlag = false;
            }
        }
    }
    mq_close(openReceiveMQ);
    return 0;
}

int main()
{
    pthread_t senderThread, receiverThread;

    // Create Send and Receive thread
    pthread_create(&senderThread, NULL, sender, NULL);
    pthread_create(&receiverThread, NULL, receiver, NULL);

    // Wait for thread stopping
    pthread_join(senderThread, NULL);
    pthread_join(receiverThread, NULL);

    return 0;
}
