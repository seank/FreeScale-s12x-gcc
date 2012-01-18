#include <string.h>

typedef unsigned char byte;

// Data structure for queues.
typedef struct {
  byte start;
  byte end;
  byte count;
  byte* data;
  byte length;
} queueType;

// Add a value to the end of a queue.
void Enqueue (queueType* queue, void *value, byte size)
{
  // Working variables.
  byte counter;
  //  byte increment = 1;

  // Save each byte of the given value at start.
  for (counter = 0; counter < size; counter++) {
    // Save byte of value.
    *(queue->data + queue->start) = *(byte*)(value++);

    // Increment start pointer (with wrap around).
    queue->start = (queue->start + 1) % queue->length;

    // Push the end forward as necessary (with wrap around). 
    //if (queue->start == queue->end) {
    //queue->end = (queue->end + 1) % queue->length;
    //  increment = 0;
    //}
  }

  // Increment element count if there was no shifting of the end pointer.
  //  if (increment) queue->count++;
}


int main()
{
  byte input = 0x10;

  static queueType queue;
  static byte buffer[5];
  queue.start = queue.end = queue.count = 0;
  queue.data = buffer;
  queue.length = 5;
  Enqueue(&queue,&input,sizeof(input));
}
