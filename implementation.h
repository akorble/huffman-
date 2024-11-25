//
// Created by Amelia Korble on 2024-11-25.
//
/*****************************************************************************
**
* Filename: <implementation.h>
* Author: Amelia korble
* Student ID: 251 336 169
* Version: 1
* Date Created: nov 25
* Last Modified: <date>
*
* Description:
* .h file for implementation.c
*
* Dependencies:
* - List any required libraries or other files
*
* Compilation:
* <Include compilation command>
*****************************************************************************/
#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#endif //IMPLEMENTATION_H
typedef struct {
    int index;            // ASCII value of the character
    unsigned int weight; // Frequency of the character
} node_t;
typedef struct QueueNode {
    node_t data;                 // The Huffman node (character and frequency)
    struct QueueNode* next;      // Pointer to the next node
} QueueNode;
typedef struct {
    QueueNode* front;            // Pointer to the front of the queue
    QueueNode* rear;             // Pointer to the rear of the queue
} Queue;
void countFrequencies(const char *filename, node_t *nodes, int *uniqueCharCount);
void initQueue(Queue* q);
void priorityEnqueue(Queue* q, node_t newNode);
void freeQueue(Queue* q);
node_t priorityDequeue(Queue* q);