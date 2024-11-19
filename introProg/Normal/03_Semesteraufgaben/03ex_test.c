/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <stdbool.h>
#include <stdio.h>

#include "03ex.c"
#include "String.h"
#include "testrunner.c"

#define TEST_NAME "03ex_test"

void render_seq(String *s, Sequence seq) {
    str_str(s, "\nelements: ");
    str_u16s(s, seq.data, seq.len);
    str_str(s, "\ncapacity: ");
    str_uint(s, seq.capacity);
    str_str(s, "\n");
}

Sequence clone_seq_rekgjnlrkeg(Sequence seq) {
    uint16_t *cloned_data = malloc(sizeof(uint16_t) * seq.capacity);
    for (size_t i = 0; i < seq.len; i++) {
        cloned_data[i] = seq.data[i];
    }
    for (size_t i = seq.len; i < seq.capacity; i++) {
        cloned_data[i] = 99;
    }
    seq.data = cloned_data;
    return seq;
}

uint16_t access_data[4] = {10, 20, 30, 99};
uint16_t access_expected[4] = {10, 20, 30, 0};

void test_get(Tester *tester) {
    if (begin_exercise(tester, "seq_get", "Aufgabe 1: Random Access")) {
        Sequence test_seq;
        test_seq.data = access_data;
        test_seq.len = 3;
        test_seq.capacity = 4;

        for (size_t index = 0; index < 4; index++) {
            if (begin_testcase(tester)) {
                String s = str_new();
                render_seq(&s, test_seq);
                str_str(&s, "\nZugriff auf Index ");
                str_uint(&s, index);

                Sequence cloned = clone_seq_rekgjnlrkeg(test_seq);
                uint16_t got = seq_get(cloned, index);
                assert_int(tester, access_expected[index], got, s.buf);

                str_free(s);
                free(cloned.data);
            }
        }

        test_seq.len = 0;
        test_seq.capacity = 1;
        for (size_t index = 0; index < 5; index++) {
            if (begin_testcase(tester)) {
                String s = str_new();
                render_seq(&s, test_seq);
                str_str(&s, "\nZugriff auf Index ");
                str_uint(&s, index);

                Sequence cloned = clone_seq_rekgjnlrkeg(test_seq);
                uint16_t got = seq_get(cloned, index);
                assert_int(tester, 0, got, s.buf);

                str_free(s);
                free(cloned.data);
            }
        }
    }
}

#define EX_PUSH_CASES 5

Sequence ex_push_input_sequences[EX_PUSH_CASES] = {
    {.data=(uint16_t[2]){10, 99}, .len=1, .capacity=2},
    {.data=(uint16_t[2]){80, 99}, .len=1, .capacity=2},
    {.data=(uint16_t[2]){99, 99}, .len=0, .capacity=2},
    {.data=(uint16_t[2]){64, 20}, .len=2, .capacity=2},
    {.data=(uint16_t[3]){33, 41, 24}, .len=3, .capacity=3},
};
uint16_t ex_push_input_numbers[EX_PUSH_CASES] = {
    66, 111, 7, 4, 41
};
Sequence ex_push_output_sequences[EX_PUSH_CASES] = {
    {.data=(uint16_t[2]){10, 66}, .len=2, .capacity=2},
    {.data=(uint16_t[2]){80, 111}, .len=2, .capacity=2},
    {.data=(uint16_t[2]){7, 99}, .len=1, .capacity=2},
    {.data=(uint16_t[4]){64, 20, 4, 99}, .len=3, .capacity=4},
    {.data=(uint16_t[6]){33, 41, 24, 41, 99, 99}, .len=4, .capacity=6},
};

char* render_exercise_2(Sequence seq, int16_t pushed)
{
    String s = str_new();
    render_seq(&s, seq);
    str_str(&s, "pushed number: ");
    str_uint(&s, pushed);
    return s.buf;
}

void assert_seq(Tester *t, Sequence expected, Sequence got, const char *context) {
    String ctx_len = str_new();
    str_str(&ctx_len, context);
    str_str(&ctx_len, "\nChecking length of the new sequence:\n");
    assert_size(t, expected.len, got.len, ctx_len.buf);
    str_free(ctx_len);


    if (expected.len == got.len) {
        String ctx_cap = str_new();
        str_str(&ctx_cap, context);
        str_str(&ctx_cap, "\nChecking capacity of the new sequence:\n");
        assert_size(t, expected.capacity, got.capacity, ctx_cap.buf);
        str_free(ctx_cap);

        assert_uint16_array(t, expected.data, got.data, expected.len, context);
    }
}

void test_push(Tester *tester) {
    if (begin_exercise(tester, "push", "Aufgabe 2: Push")) {
        for (size_t i = 0; i < EX_PUSH_CASES; i++) {
            if (begin_testcase(tester)) {
                char *args = render_exercise_2(ex_push_input_sequences[i], ex_push_input_numbers[i]);
                Sequence cloned = clone_seq_rekgjnlrkeg(ex_push_input_sequences[i]);

                seq_push(&cloned, ex_push_input_numbers[i]);

                assert_seq(tester, ex_push_output_sequences[i], cloned, args);

                free(args);
                free(cloned.data);
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror " TEST_NAME ".c -o " TEST_NAME ".o -lm && ./" TEST_NAME ".o");

    test_get(&tester);
    test_push(&tester);

    return wrap_up(&tester);
}
