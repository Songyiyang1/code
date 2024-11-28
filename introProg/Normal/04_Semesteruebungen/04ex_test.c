/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "04ex.c"
#include "testrunner.c"

#define TEST_NAME "04ex_test"

typedef struct {
    int initial_values[10]; // Initial values for the list
    int initial_size;       // Number of initial values
    int expected_size;      // Expected size of the list after prepend
    const char *expected;   // Expected list state after prepend
} PrependTestCase;

typedef struct {
    int initial_values[10]; // Initial values for the list
    int initial_size;       // Number of initial values
    const char *expected;   // Expected list state after reverse
} ReverseTestCase;

PrependTestCase prepend_test_cases[] = {
        {{3, 2, 1}, 3, 3, "[1, 2, 3]"},
        {{5}, 1, 1, "[5]"},
        {{10, 20, 30, 40}, 4, 4, "[40, 30, 20, 10]"},
        {{}, 0, 0, "[]"},
};

ReverseTestCase reverse_test_cases[] = {
        {{1, 2, 3}, 3, "[3, 2, 1]"},
        {{5}, 1, "[5]"},
        {{1, 2, 3, 4, 5}, 5, "[5, 4, 3, 2, 1]"},
        {{1, 2}, 2, "[2, 1]"},
        {{}, 0, "[]"},
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

void test_prepend(Tester *tester) {
    if (begin_exercise(tester, "prepend", "Aufgabe 1: Einfügen am Anfang")) {
        for (int i = 0; i < sizeof(prepend_test_cases) / sizeof(prepend_test_cases[0]); i++) {
            PrependTestCase *tc = &prepend_test_cases[i];
            if (begin_testcase(tester)) {
                DoublyLinkedList list;
                init_list(&list);

                for (int j = 0; j < tc->initial_size; j++) {
                    prepend(&list, tc->initial_values[j]);
                }

                char buffer[100];
                char message[200];
                list_to_str(&list, buffer, sizeof(buffer));
                snprintf(message, sizeof(message), "Erwartet: %s, erhalten: %s", tc->expected, buffer);

                assert_bool(tester, true, strcmp(buffer, tc->expected) == 0, message);
                assert_int(tester, tc->expected_size, list.size, "Falsche Größe der Liste");

                free_list(&list);
            }
        }
    }
}

void test_reverse(Tester *tester) {
    if (begin_exercise(tester, "reverse", "Aufgabe 2: Umkehren der Liste")) {
        for (int i = 0; i < sizeof(reverse_test_cases) / sizeof(reverse_test_cases[0]); i++) {
            ReverseTestCase *tc = &reverse_test_cases[i];
            if (begin_testcase(tester)) {
                DoublyLinkedList list;
                init_list(&list);

                for (int j = 0; j < tc->initial_size; j++) {
                    append(&list, tc->initial_values[j]);
                }
                reverse(&list);

                char buffer[100];
                char message[200];
                list_to_str(&list, buffer, sizeof(buffer));
                snprintf(message, sizeof(message), "Erwartet: %s, erhalten: %s", tc->expected, buffer);

                assert_bool(tester, true, strcmp(buffer, tc->expected) == 0, message);

                free_list(&list);
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror " TEST_NAME ".c -o " TEST_NAME ".o -lm && ./" TEST_NAME ".o");

    test_prepend(&tester);
    test_reverse(&tester);

    return wrap_up(&tester);
}
