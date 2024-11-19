/* This must be the first thing of any test file: */
#include "system.h"
/* End of first thing. */

#include <stdbool.h>
#include <stdio.h>

#include "03ex.c"
#include "String.h"
#include "testrunner.c"

#define TEST_NAME "03ex_test"

void render_seq(String *s, Sequence seq)
{
    str_str(s, "\nelements: ");
    str_u16s(s, seq.data, seq.len);
    str_str(s, "\ncapacity: ");
    str_uint(s, seq.capacity);
    str_str(s, "\n");
}

Sequence clone_seq_rekgjnlrkeg(Sequence seq)
{
    uint16_t *cloned_data = malloc(sizeof(uint16_t) * seq.capacity);
    for (size_t i = 0; i < seq.len; i++)
    {
        cloned_data[i] = seq.data[i];
    }
    for (size_t i = seq.len; i < seq.capacity; i++)
    {
        cloned_data[i] = 99;
    }
    seq.data = cloned_data;
    return seq;
}

void assert_seq(Tester *t, Sequence expected, Sequence got, const char *context)
{
    String ctx_len = str_new();
    str_str(&ctx_len, context);
    str_str(&ctx_len, "\nChecking length of the new sequence:\n");
    assert_size(t, expected.len, got.len, ctx_len.buf);
    str_free(ctx_len);

    if (expected.len == got.len)
    {
        String ctx_cap = str_new();
        str_str(&ctx_cap, context);
        str_str(&ctx_cap, "\nChecking capacity of the new sequence:\n");
        assert_size(t, expected.capacity, got.capacity, ctx_cap.buf);
        str_free(ctx_cap);

        assert_uint16_array(t, expected.data, got.data, expected.len, context);
    }
}

#define EX_FILTER_CASES 6

Sequence ex_filter_in[EX_FILTER_CASES] = {
    {.data = (uint16_t[6]){0, 1, 2, 3, 4, 99}, .len = 5, .capacity = 5},
    {.data = (uint16_t[2]){17, 99}, .len = 1, .capacity = 2},
    {.data = (uint16_t[2]){80, 99}, .len = 1, .capacity = 2},
    {.data = (uint16_t[2]){99, 99}, .len = 0, .capacity = 2},
    {.data = (uint16_t[3]){2, 4, 6}, .len = 3, .capacity = 3},
    {.data = (uint16_t[5]){2, 77, 33, 4, 6}, .len = 5, .capacity = 5},
};
Sequence ex_filter_out[EX_FILTER_CASES] = {
    {.data = (uint16_t[6]){0, 2, 4, 99, 99, 99}, .len = 3, .capacity = 5},
    {.data = (uint16_t[2]){99, 99}, .len = 0, .capacity = 2},
    {.data = (uint16_t[2]){80, 99}, .len = 1, .capacity = 2},
    {.data = (uint16_t[2]){99, 99}, .len = 0, .capacity = 2},
    {.data = (uint16_t[3]){2, 4, 6}, .len = 3, .capacity = 3},
    {.data = (uint16_t[5]){2, 4, 6, 99, 99}, .len = 3, .capacity = 5},
};

void do_test_1(Tester *tester, Sequence in, Sequence out)
{
    Sequence copy = clone_seq_rekgjnlrkeg(in);
    seq_remove_odds(&copy);

    String s = str_new();
    str_str(&s, "Eingabesequenz:");
    render_seq(&s, in);
    assert_seq(tester, out, copy, s.buf);

    str_free(s);
    free(copy.data);
}

void test_filter(Tester *tester)
{
    if (begin_exercise(tester, "seq_remove_odds", "Aufgabe 1: Filtern"))
    {
        for (size_t i = 0; i < EX_FILTER_CASES; i++)
        {
            if (begin_testcase(tester))
            {
                do_test_1(tester, ex_filter_in[i], ex_filter_out[i]);
            }
        }
    }
}

#define EX_APPEND_CASES 7

Sequence ex_append_in[EX_APPEND_CASES] = {
    {.data = (uint16_t[6]){0, 0, 0, 99, 99, 99}, .len = 3, .capacity = 6},
    {.data = (uint16_t[6]){0, 0, 0, 99, 99, 99}, .len = 3, .capacity = 6},
    {.data = (uint16_t[6]){0, 0, 0, 99, 99, 99}, .len = 3, .capacity = 6},
    {.data = (uint16_t[6]){0, 0, 0, 99, 99, 99}, .len = 3, .capacity = 6},
    {.data = (uint16_t[6]){0, 0, 0, 99, 99, 99}, .len = 3, .capacity = 6},
    {.data = (uint16_t[6]){0, 0, 0, 99, 99, 99}, .len = 3, .capacity = 6},
    {.data = (uint16_t[2]){99, 99}, .len = 0, .capacity = 0},
};

size_t ex_append_n[EX_APPEND_CASES] = {
    0,
    1,
    2,
    3,
    4,
    5,
    3,
};

Sequence ex_append_out[EX_APPEND_CASES] = {
    {.data = (uint16_t[6]){0, 0, 0, 99, 99, 99}, .len = 3, .capacity = 6},
    {.data = (uint16_t[6]){0, 0, 0, 1, 99, 99}, .len = 4, .capacity = 6},
    {.data = (uint16_t[6]){0, 0, 0, 1, 1, 99}, .len = 5, .capacity = 6},
    {.data = (uint16_t[6]){0, 0, 0, 1, 1, 1}, .len = 6, .capacity = 6},
    {.data = (uint16_t[7]){0, 0, 0, 1, 1, 1, 1}, .len = 7, .capacity = 7},
    {.data = (uint16_t[8]){0, 0, 0, 1, 1, 1, 1, 1}, .len = 8, .capacity = 8},
    {.data = (uint16_t[3]){1, 1, 1}, .len = 3, .capacity = 3},
};

void do_test_2(Tester *tester, Sequence in, size_t n, Sequence out)
{
    Sequence copy = clone_seq_rekgjnlrkeg(in);
    seq_append_ones(&copy, n);

    String s = str_new();
    str_str(&s, "Eingabesequenz:");
    render_seq(&s, in);
    str_str(&s, "Anzahl Einsen: ");
    str_uint(&s, n);
    str_str(&s, "\n");
    assert_seq(tester, out, copy, s.buf);

    str_free(s);
    free(copy.data);
}

void test_append_ones(Tester *tester)
{
    if (begin_exercise(tester, "seq_append_ones", "Aufgabe 2: Einsen anhängen"))
    {
        for (size_t i = 0; i < EX_APPEND_CASES; i++)
        {
            if (begin_testcase(tester))
            {
                do_test_2(tester, ex_append_in[i], ex_append_n[i], ex_append_out[i]);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    Tester tester = tester_new(argc - 1, argv[1], argv[2],
                               "clang -std=c11 -g -Wall -Werror " TEST_NAME ".c -o " TEST_NAME ".o -lm && ./" TEST_NAME ".o");

    test_filter(&tester);
    test_append_ones(&tester);

    return wrap_up(&tester);
}
