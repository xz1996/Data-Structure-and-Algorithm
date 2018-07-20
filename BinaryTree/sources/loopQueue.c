#include "LoopQueue.h"

bool enqueue(LoopQueue* loopQ, queueDataType data)
{
    if (loopQ == NULL)
    {
        printf("there is no such loop queue!\n");
        return false;
    }

    if (isFull(loopQ))
    {
        printf("the loop queue is full!\n");
        return false;
    }
    else
    {
        loopQ -> rear = ((loopQ -> rear) + 1) % Q_MAX_SIZE;
        loopQ -> queue[loopQ -> rear] = data;
        return true;
    }
}

queueDataType dequeue(LoopQueue* loopQ)
{
    if (loopQ == NULL)
    {
        printf("there is no such loop queue!\n");
        return NULL;
    }
    if (isEmpty(loopQ))
    {
        printf("the loop queue is empty!\n");
        return NULL;
    }
    else
    {
        loopQ -> front = ((loopQ -> front) + 1) % Q_MAX_SIZE;
        return loopQ -> queue[loopQ -> front];
    }
}

int getQueueSize(LoopQueue* loopQ)
{
    return ((loopQ -> rear) - (loopQ -> front) + Q_MAX_SIZE) % Q_MAX_SIZE;
}

bool isFull(LoopQueue* loopQ)
{
    if (((loopQ -> rear) + 1) % Q_MAX_SIZE == (loopQ -> front))
        return true;
    else
        return false;
}

bool isEmpty(LoopQueue* loopQ)
{
    if ((loopQ -> rear) == (loopQ -> front))
        return true;
    else
        return false;
}