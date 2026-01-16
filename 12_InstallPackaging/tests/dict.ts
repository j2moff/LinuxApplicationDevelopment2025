#include <check.h>
#include "../src/dict.h"

#test test_get_char_type
ck_assert_int_eq(get_char_type(L'а', L'б'), STRAIGHT);
ck_assert_int_eq(get_char_type(L'я', L'б'), QUEER_SOFT);
ck_assert_int_eq(get_char_type(L'я', L'а'), QUEER_IOTA);
ck_assert_int_eq(get_char_type(L'и', L'ь'), I_IOTA);
ck_assert_int_eq(get_char_type(L'и', L'б'), I_SOFT);
ck_assert_int_eq(get_char_type(L'ъ', L'б'), HARD_SIGN);
ck_assert_int_eq(get_char_type(L'.', L'б'), ELSE);

#test test_translit_char
const translit_pair test_translit_table[] = {{L'е', L"je"}};
const wchar_t *translit = translit_char(L'е', test_translit_table, 1);

ck_assert_ptr_nonnull(translit);
ck_assert_int_eq(translit[0], L'j');
ck_assert_int_eq(translit[1], L'e');

