#ifndef LOOP_QUEUE
#define LOOP_QUEUE

/* ------------- header reference --------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ---------------- macro define --------------- */

#define Q_MAX_SIZE 10           // Note that the actual max size is one unit less than Q_MAX_SIZE.

typedef int queueDataType;

/* ---------------- struct declaration ------------ */

typedef struct loopQueue
{
    int front;
    int rear;
    queueDataType queue[Q_MAX_SIZE];
} LoopQueue;

/* ------------- method declaration -------------- */

bool enqueue(LoopQueue* loopQ, queueDataType data);

queueDataType dequeue(LoopQueue* loopQ);

int getQueueSize(LoopQueue* loopQ);

bool isFull(LoopQueue* loopQ);

bool isEmpty(LoopQueue* loopQ);

#endif // LOOP_QUEUE