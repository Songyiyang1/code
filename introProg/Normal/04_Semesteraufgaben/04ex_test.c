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
    int initial_values[10];    // Values to append to the list
    int initial_size;          // Number of values to append
    int value_to_find;         // Value to find in the list
    bool expect_found;         // Expected outcome of finding the value
    int expected_found_value;  // Expected value of the found node (if any)
} FindNodeTestCase;

typedef struct {
    int initial_values[10];    // Holds initial values for the list
    int initial_size;          // Number of initial values
    int value_to_remove;       // Value to remove (if applicable)
    bool expect_removed;       // Expected result of the remove operation
    int expected_size;         // Expected size of the list after the operation
    const char *expected_list; // Expected list state as a string
} RemoveNodeTestCase;

typedef struct {
    int values[10];             // Values to append
    int size;                   // Number of values to append
    int value_to_remove;        // Value to remove
    int expected_removed_count; // Expected count of removed nodes
    const char *expected_list;  // Expected list state as a string
} RemoveAllTestCase;

FindNodeTestCase find_node_test_cases[] = {
        {{1, 2, 3}, 3, 2, true,  2},
        {{1, 2, 3}, 3, 4, false, -1},
        {{},        0, 1, false, -1}
};

RemoveNodeTestCase remove_node_test_cases[] = {
        {{1, 2, 3, 2}, 4, 2, true,  3, "[1, 3, 2]"},
        {{},           0, 1, false, 0, "[]"},
        {{1},          1, 1, true,  0, "[]"},
        {{1, 2, 3},    3, 1, true,  2, "[2, 3]"}
};

RemoveAllTestCase remove_all_test_cases[] = {
        {{1, 2, 2, 3},       4, 2, 2, "[1, 3]"},
        {{},                 0, 1, 0, "[]"},
        {{1, 1, 1},          3, 1, 3, "[]"},
        {{1, 2, 3, 2, 4, 2}, 6, 2, 3, "[1, 3, 4]"}
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

void test_find_node(Tester *tester) {
    if (begin_exercise(tester, "find_node", "Aufgabe 2: Suche")) {
        for (int i = 0; i < sizeof(find_node_test_cases) / sizeof(find_node_test_cases[0]); i++) {
            FindNodeTestCase *tc = &find_node_test_cases[i];
            if (begin_testcase(tester)) {
                DoublyLinkedList list;
                init_list(&list);
                for (int j = 0; j < tc->initial_size; j++) {
                    append(&list, tc->initial_values[j]);
                }
                Node *node = find_node(&list, tc->value_to_find);

                char buffer[100];
                char context[200];
                list_to_str(&list, buffer, sizeof(buffer));
                snprintf(context, sizeof(context), "Suche nach Knoten mit Wert %d in Liste %s\n", tc->value_to_find, buffer);

                assert_bool(tester, tc->expect_found, node != NULL, context);
                if (tc->expect_found) {
                    snprintf(context + strlen(context), sizeof(context) - strlen(context),
                             "Gefundener Knotenwert: %d, Erwarteter Knotenwert: %d\n", node->data, tc->expected_found_value);

                    assert_int(tester, tc->expected_found_value, node->data, context);
                }

                free_list(&list);
            }
        }
    }
}

void test_remove_node(Tester *tester) {
    if (begin_exercise(tester, "remove_node", "Aufgabe 3: Löschen")) {
        for (int i = 0; i < sizeof(remove_node_test_cases) / sizeof(remove_node_test_cases[0]); i++) {
            RemoveNodeTestCase *tc = &remove_node_test_cases[i];
            if (begin_testcase(tester)) {
                DoublyLinkedList list;
                init_list(&list);
                for (int j = 0; j < tc->initial_size; j++) {
                    append(&list, tc->initial_values[j]);
                }

                char buffer[100];
                char context[200];
                list_to_str(&list, buffer, sizeof(buffer));
                snprintf(context, sizeof(context), "Liste: %s\n", buffer);

                bool removed = remove_node(&list, tc->value_to_remove);
                list_to_str(&list, buffer, sizeof(buffer));
                snprintf(context + strlen(context), sizeof(context) - strlen(context),
                         "Liste nach remove_node(%d): %s\n", tc->value_to_remove, buffer);

                assert_bool(tester, tc->expect_removed, removed, context);
                assert_size(tester, tc->expected_size, list.size, context);
                assert_bool(tester, true, strcmp(buffer, tc->expected_list) == 0, context);

                free_list(&list);
            }
        }
    }
}

void test_remove_all(Tester *tester) {
    if (begin_exercise(tester, "remove_all", "Aufgabe 4: Löschen aller Vorkommen")) {
        for (int i = 0; i < sizeof(remove_all_test_cases) / sizeof(remove_all_test_cases[0]); i++) {
            RemoveAllTestCase *tc = &remove_all_test_cases[i];
            if (begin_testcase(tester)) {
                DoublyLinkedList list;
                init_list(&list);
                for (int j = 0; j < tc->size; j++) {
                    append(&list, tc->values[j]);
                }

                char buffer[100];
                char context[200];
                list_to_str(&list, buffer, sizeof(buffer));
                snprintf(context, sizeof(context), "Liste: %s\n", buffer);

                int removed_count = remove_all(&list, tc->value_to_remove);
                list_to_str(&list, buffer, sizeof(buffer));
                snprintf(context + strlen(context), sizeof(context) - strlen(context),
                         "Liste nach remove_all(%d): %s\n", tc->value_to_remove, buffer);

                assert_int(tester, tc->expected_removed_count, removed_count, context);
                assert_bool(tester, true, strcmp(buffer, tc->expected_list) == 0, context);

                free_list(&list);
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror " TEST_NAME ".c -o " TEST_NAME ".o -lm && ./" TEST_NAME ".o");

    test_find_node(&tester);
    test_remove_node(&tester);
    test_remove_all(&tester);

    return wrap_up(&tester);
}
