#include "loopQueue.h"

int main()
{
    LoopQueue loopQ;
    loopQ.front = 0;
    loopQ.rear = 0;
    LoopQueue* loopQueue = &loopQ;

    // Enqueue
    printf("enqueue:\n");

    for (int i = 0; !isFull(loopQueue); i++)
    {
        enqueue(loopQueue, i);
    }
    printf("the queue size after enqueue is %d.\n", getQueueSize(loopQueue));
    if (enqueue(loopQueue, 11))
    {
        printf("enqueue successfully.\n");
    }
    else
    {
        printf("enqueue error!\n");
    }

    // Dequeue
    printf("dequeue:\n");
    while(!isEmpty(loopQueue))
    {
        printf("%d ", dequeue(loopQueue));
    }
    printf("\n");
    printf("the queue size after dequeue is %d.\n", getQueueSize(loopQueue));

    if (-1 == dequeue(loopQueue))
    {
        printf("dequeue error!\n");
    }
    else
    {
        printf("dequeue successfully.\n");
    }
    return 0;
}