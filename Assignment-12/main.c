#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    struct Queue *queue = createQueue();

    while (1)
    {
        printf("1. To ENQUEUE");
        printf("\n2. To DEQUEUE");
        printf("\n3. To DISPLAY");
        printf("\n4. TO Empty QUEUE");
        printf("\n5. To EXIT");
        printf("\nPlease make a choice: ");
        int choice;
        scanf("%d", &choice);
        system("cls");

        if (choice == 1)
        {
            int data;
            while (1)
            {
                
                printf("Enter the data and -999 to exit: ");
                scanf("%d", &data);

                if (data == -999)
                {
                    break;
                }

                enqueue(queue, data);

                system("cls");

                displayQueue(queue);

            }

            printf("----------------------------\n");
        }
        else if (choice == 2)
        {

            dequeue(queue);
            displayQueue(queue);

            printf("----------------------------\n");
        }
        else if (choice == 3)
        {

            displayQueue(queue);

            printf("----------------------------\n");
        }
        else if (choice == 4)
        {

            emptyQueue(queue);
            displayQueue(queue);

            printf("----------------------------\n");
        }
        else if (choice == 5)
        {
            break;
        }
    }

    return 0;
}
