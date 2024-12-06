/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "06ex.c"
#include "testrunner.c"

#define TEST_NAME "06ex_test"

typedef struct {
    int initial_values[10];    // Initial values to populate the list
    int initial_size;          // Number of initial values
    const char *expected_list; // Expected sorted list as a string
    int expected_head;         // Expected head value after sorting
    int expected_tail;         // Expected tail value after sorting
    size_t expected_size;         // Expected size of the list
} SortListTestCase;

SortListTestCase sort_list_test_cases[] = {
        {{},                       0, "[]",                   -1,   -1,  0}, // Empty list
        {{42},                     1, "[42]",                 42,   42,  1}, // Single element list
        {{2,   1},                 2, "[1, 2]",               1,    2,   2}, // Two elements, reversed
        {{5,   3,  1,  4,  2},     5, "[1, 2, 3, 4, 5]",      1,    5,   5}, // Small random list
        {{-3,  -1, -2, -5, -4},    5, "[-5, -4, -3, -2, -1]", -5,   -1,  5}, // List with negative numbers
        {{10,  20, 30, 40, 50},    5, "[10, 20, 30, 40, 50]", 10,   50,  5}, // Already sorted list
        {{50,  40, 30, 20, 10},    5, "[10, 20, 30, 40, 50]", 10,   50,  5}, // Reverse sorted list
        {{7,   -1, 0,  3,  -5, 4}, 6, "[-5, -1, 0, 3, 4, 7]", -5,   7,   6}, // Mixed positive and negative values
        {{100, -100},              2, "[-100, 100]",          -100, 100, 2}  // Two elements with large difference
};

void list_to_str(const DoublyLinkedList *list, char *buffer, size_t buffer_size) {
    Node *current = list->head;
    size_t offset = 0;

    if (offset < buffer_size - 1) {
        offset += snprintf(buffer + offset, buffer_size - offset, "[");
    }

    while (current != NULL && offset < buffer_size - 1) {
        offset += snprintf(buffer + offset, buffer_size - offset, "%d", current->data);
        current = current->next;

        if (current != NULL && offset < buffer_size - 1) {
            offset += snprintf(buffer + offset, buffer_size - offset, ", ");
        }
    }

    if (offset < buffer_size - 1) {
        offset += snprintf(buffer + offset, buffer_size - offset, "]");
    }

    if (offset < buffer_size) {
        buffer[offset] = '\0';
    }
}

bool verify_list(const DoublyLinkedList *list, const SortListTestCase *tc, char *error_message, size_t error_message_size) {
    if (list->head == NULL && list->tail == NULL && list->size == 0) {
        return true;
    }

    Node *current = list->head;
    Node *prev = NULL;
    size_t count = 0;

    while (current != NULL) {
        if (current->prev != prev) {
            snprintf(error_message, error_message_size,
                     "Erwarteter prev von %d: %d, erhalten: %d",
                     current->data, prev == NULL ? -1 : prev->data, current->prev == NULL ? -1 : current->prev->data);
            return false;
        }

        prev = current;
        current = current->next;
        count++;
    }

    if (list->head == NULL) {
        snprintf(error_message, error_message_size, "Erwarteter head: %d, erhalten: NULL", tc->expected_head);
        return false;
    }

    if (list->head->data != tc->expected_head) {
        snprintf(error_message, error_message_size, "Erwarteter head: %d, erhalten: %d", tc->expected_head,
                 list->head->data);
        return false;
    }

    if (list->tail == NULL) {
        snprintf(error_message, error_message_size, "Erwarteter tail: %d, erhalten: NULL", tc->expected_tail);
        return false;
    }

    if (list->tail->data != tc->expected_tail) {
        snprintf(error_message, error_message_size, "Erwarteter tail: %d, erhalten: %d", tc->expected_tail,
                 list->tail->data);
        return false;
    }

    if (count != list->size) {
        snprintf(error_message, error_message_size, "Erwarteter size: %zu, erhalten: %zu", tc->expected_size,
                 list->size);
        return false;
    }

    return true;
}

void init_list(DoublyLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void append(DoublyLinkedList *list, int data) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }

    list->tail = new_node;
    list->size++;
}

void free_list(DoublyLinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void test_sort_list(Tester *tester) {
    if (begin_exercise(tester, "sort_list", "Aufgabe 1: Sortieren")) {
        for (int i = 0; i < sizeof(sort_list_test_cases) / sizeof(sort_list_test_cases[0]); i++) {
            SortListTestCase *tc = &sort_list_test_cases[i];
            if (begin_testcase(tester)) {
                DoublyLinkedList list;
                init_list(&list);

                for (int j = 0; j < tc->initial_size; j++) {
                    append(&list, tc->initial_values[j]);
                }

                char buffer[100];
                char context[200];
                list_to_str(&list, buffer, sizeof(buffer));
                snprintf(context, sizeof(context), "Liste vor sort_list: %s\n", buffer);

                sort_list(&list);

                list_to_str(&list, buffer, sizeof(buffer));
                snprintf(context + strlen(context), sizeof(context) - strlen(context),
                         "Liste nach sort_list: %s\n", buffer);

                assert_bool(tester, true, strcmp(buffer, tc->expected_list) == 0, context);

                char error_message[200];
                bool is_consistent = verify_list(&list, tc, error_message, sizeof(error_message));
                if (!is_consistent) {
                    snprintf(context + strlen(context), sizeof(context) - strlen(context),
                             "%s\n", error_message);
                }

                assert_bool(tester, true, is_consistent, context);

                free_list(&list);
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror " TEST_NAME ".c -o " TEST_NAME ".o -lm && ./" TEST_NAME ".o");

    test_sort_list(&tester);

    return wrap_up(&tester);
}
