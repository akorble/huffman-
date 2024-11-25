//
// Created by Amelia Korble on 2024-11-25.
//
#include <stdio.h>
#include <stdlib.h>
#include "implementation.h"
/*****************************************************************************
**
* Filename: <implementation.c>
* Author: Amelia Korble
* Student ID: 251 336 169
* Version: 1
* Date Created: Nov 25
* Last Modified: <date>
*
* Description:
* The countFrequencies function reads an input file, counts the occurrences of each character, and stores these frequencies in an array of node_t structures. Each node_t structure holds the ASCII value of the character (index) and its frequency (weight).
It updates the count of unique characters in the file and returns it
*priorityEnqueue inserts a new node into the queue in sorted order, ensuring that nodes are ordered by their frequency, with the smallest frequency node at the front of the queue
*priorityDequeue removes and returns the node_t from the front of the queue. The node with the smallest weight (highest priority) is dequeued first. If the queue is empty, the function will exit
*The initQueue and freeQueue functions do basic memory management (initialize and free the queue memory)
* Dependencies:
* <stdio.h>
*<stdlib.h>
*#include "implementation.h"
*huffman_tree.c file to be written will implement this code
*
* Compilation:
* <Include compilation command>
*****************************************************************************/
// Structure definition for a Huffman tree node
// Function to count character frequencies and store them in the nodes array
void countFrequencies(const char *filename, node_t *nodes, int *uniqueCharCount) {
    // Step 1: Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s'\n", filename);
        exit(1);
    }

    // Step 2: Initialize frequency array
    int frequencies[256] = {0}; // One entry for each ASCII character

    // Step 3: Read characters and count occurrences
    int c; // Variable to store each character read from the file
    while ((c = fgetc(file)) != EOF) {
        frequencies[c]++;
    }

    // Step 4: Populate the nodes array with non-zero frequencies
    int nodeIndex = 0; // Keeps track of how many nodes we've added
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            nodes[nodeIndex].index = i;          // ASCII value of the character
            nodes[nodeIndex].weight = frequencies[i]; // Frequency of the character
            nodeIndex++;
        }
    }

    // Step 5: Store the number of unique characters
    *uniqueCharCount = nodeIndex;

    // Step 6: Close the file
    fclose(file);
}
 //function auto intialize the queue for enqueueing in priority
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Function to insert a node into the queue in sorted order
void priorityEnqueue(Queue* q, node_t newNode) {
    QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newQueueNode) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
        newQueueNode->data = newNode;
        newQueueNode->next = NULL;

        // If the queue is empty, insert at the front
        if (q->front == NULL) {
            q->front = q->rear = newQueueNode;
            return;
        }

        // If the new node has a smaller weight than the front node, insert at the front
        if (newNode.weight < q->front->data.weight) {
            newQueueNode->next = q->front;
            q->front = newQueueNode;
            return;
        }

        // Traverse to find the insertion point
        QueueNode* current = q->front;
        while (current->next != NULL && current->next->data.weight <= newNode.weight) {
            current = current->next;
        }

        // Insert the new node
        newQueueNode->next = current->next;
        current->next = newQueueNode;

        // Update the rear if inserted at the end
        if (newQueueNode->next == NULL) {
            q->rear = newQueueNode;
        }
    }
    void freeQueue(Queue* q){
        QueueNode* current = q->front;
        while (current != NULL) {
            QueueNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
// Function to dequeue the node with the highest priority (lowest weight)
node_t priorityDequeue(Queue* q) {
    if (q->front == NULL) {
        fprintf(stderr, "Queue is empty! Cannot dequeue.\n");
        exit(1); // or return a default value, but exiting is safer for now
    }

    // Store the data of the front node to return
    QueueNode* temp = q->front;
    node_t dequeuedNode = temp->data;

    // Move the front pointer to the next node
    q->front = q->front->next;

    // If the queue is now empty, set rear to NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // Free the memory of the dequeued node
    free(temp);

    return dequeuedNode;
}
