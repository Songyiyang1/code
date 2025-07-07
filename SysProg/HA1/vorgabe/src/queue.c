#include "../lib/queue.h"
#include "stdlib.h"

#include <stdio.h>

int queue_add(void *new_object, queue_object *queue) {
  // TODO
  queue_object *object = (queue_object *)malloc(sizeof(queue_object));
  if (object == NULL) {
    perror("Error allocating memory");
    return 1;
  }
  object->next = queue->next;
  queue->next = object;
  object->object = new_object;
  return 0;
}

void *queue_poll(queue_object *queue) {
  // TODO
  if (queue == NULL || queue->next == NULL)
    return NULL;
  while (queue->next->next != NULL)
    queue = queue->next;
  void *object = queue->next->object;
  free(queue->next);
  queue->next = NULL;
  return object;
}

queue_object *new_queue() {
  // TODO
  queue_object *queue = (queue_object *)malloc(sizeof(queue_object));
  if (queue == NULL) {
    perror("Error allocating memory");
    return NULL;
  }
  queue->next = NULL;
  queue->object = NULL;
  return queue;
}

void free_queue(queue_object *queue) {
  // TODO
  while (queue->next != NULL)
    queue_poll_tail(queue);
  free(queue);
}

void *queue_peek(queue_object *queue) {
  // TODO
  if (queue == NULL)
    return NULL;
  while (queue->next != NULL)
    queue = queue->next;
  return queue->object;
}

void *queue_poll_tail(queue_object *queue) {
  // TODO
  if (queue == NULL || queue->next == NULL)
    return NULL;
  queue_object *temp = queue->next->next;
  void *object = queue->next->object;
  free(queue->next);
  queue->next = temp;
  return object;
}