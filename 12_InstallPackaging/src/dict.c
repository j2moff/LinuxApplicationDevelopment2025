#include "dict.h"
#include <wchar.h>
#include <stdio.h>

/**
 * @brief Cyrillic characters that can be transliterated straightforward
 */
static const wchar_t *straight_chars = L"абвгджзйклмнопрстуфхцчшщыьэАБВГДЖЗЙКЛМНОПРСТУФХЦЧШЩЫЬЭ";

/**
 * @brief Cyrillic characters (soft vowels) whose translitiration is affected by the previous character
 */
static const wchar_t *queer_chars = L"еёюяЕЁЮЯ";

/**
 * @brief Cyrillic consonants that affect the next soft vowel transliteration
 */
static const wchar_t *softing_chars = L"бвгджзклмнпрстфхцчшщБВГДЖЗКЛМНПРСТФХЦЧШЩ";

char_type get_char_type(wchar_t curr_char, wchar_t prev_char){
    if (wcschr(straight_chars, curr_char) != NULL)
        return STRAIGHT;

    if (wcschr(queer_chars, curr_char) != NULL) {
        if (wcschr(softing_chars, prev_char) != NULL)
            return QUEER_SOFT;

        return QUEER_IOTA;
    }

    if (curr_char == L'и' || curr_char == L'И') {
        if (prev_char == L'ь' || prev_char == L'Ь')
            return I_IOTA;
        return I_SOFT;
    }

    if (curr_char == L'ъ' || curr_char == L'Ъ')
        return HARD_SIGN;

    return ELSE;
};

/**
 * @brief Straightforward transliteration rules
 */
static const translit_pair straight_translit_table[] = {
    {L'а', L"a"}, {L'б', L"b"}, {L'в', L"v"}, {L'г', L"g"},
    {L'д', L"d"}, {L'ж', L"ž"}, {L'з', L"z"}, {L'й', L"j"},
    {L'к', L"k"}, {L'л', L"l"}, {L'м', L"m"}, {L'н', L"n"},
    {L'о', L"o"}, {L'п', L"p"}, {L'р', L"r"}, {L'с', L"s"},
    {L'т', L"t"}, {L'у', L"u"}, {L'ф', L"f"}, {L'х', L"h"},
    {L'ц', L"c"}, {L'ч', L"ç"}, {L'ш', L"š"}, {L'щ', L"ş"},
    {L'ы', L"y"}, {L'ь', L"\'"}, {L'э', L"ê"},

    {L'А', L"A"}, {L'Б', L"B"}, {L'В', L"V"}, {L'Г', L"G"},
    {L'Д', L"D"}, {L'Ж', L"Ž"}, {L'З', L"Z"}, {L'Й', L"J"},
    {L'К', L"K"}, {L'Л', L"L"}, {L'М', L"M"}, {L'Н', L"N"},
    {L'О', L"O"}, {L'П', L"P"}, {L'Р', L"R"}, {L'С', L"S"},
    {L'Т', L"T"}, {L'У', L"U"}, {L'Ф', L"F"}, {L'Х', L"H"},
    {L'Ц', L"C"}, {L'Ч', L"Ç"}, {L'Ш', L"Š"}, {L'Щ', L"Ş"},
    {L'Ы', L"Y"}, {L'Ь', L"\'"}, {L'Э', L"Ê"},
};

/**
 * @brief Soft vowel after a consonant transliteration rules
 */
static const translit_pair soft_translit_table[] = {
    {L'е', L"e"}, {L'ё', L"ó"}, {L'ю', L"ú"}, {L'я', L"á"},
    {L'Е', L"E"}, {L'Ё', L"Ó"}, {L'Ю', L"Ú"}, {L'Я', L"Á"},
};

/**
 * @brief Soft vowel after other character transliteration rules
 */
static const translit_pair iota_translit_table[] = {
    {L'е', L"je"}, {L'ё', L"jo"}, {L'ю', L"ju"}, {L'я', L"ja"},
    {L'Е', L"Je"}, {L'Ё', L"Jo"}, {L'Ю', L"Ju"}, {L'Я', L"Ja"},
};

/**
 * @brief "I" after a soft sign transliteration rules
 */
static const translit_pair i_iota_translit_table[] = {
    {L'и', L"ji"}, {L'И', L"Ji"},
};

/**
 * @brief "I" after other character transliteration rules
 */
static const translit_pair i_soft_translit_table[] = {
    {L'и', L"i"}, {L'И', L"I"},
};

static const size_t straight_translit_table_size = sizeof(straight_translit_table) / sizeof(translit_pair);
static const size_t soft_translit_table_size = sizeof(soft_translit_table) / sizeof(translit_pair);
static const size_t iota_translit_table_size = sizeof(iota_translit_table) / sizeof(translit_pair);
static const size_t i_iota_translit_table_size = sizeof(i_iota_translit_table) / sizeof(translit_pair);
static const size_t i_soft_translit_table_size = sizeof(i_soft_translit_table) / sizeof(translit_pair);

const wchar_t* translit_char(wchar_t curr_char, const translit_pair *translit_table, const size_t translit_table_size) {
    for (size_t i = 0; i < translit_table_size; i++)
        if (translit_table[i].cyr_char == curr_char)
            return translit_table[i].lat_char;

    return NULL;
}

void convert_and_print(wchar_t curr_char, wchar_t prev_char, FILE* outfile) {
    char_type char_type = get_char_type(curr_char, prev_char);

    const translit_pair *translit_table;
    size_t translit_table_size;

    switch (char_type)
    {
    case STRAIGHT:
        translit_table = straight_translit_table;
        translit_table_size = straight_translit_table_size;
        break;

    case QUEER_SOFT:
        translit_table = soft_translit_table;
        translit_table_size = soft_translit_table_size;
        break;

    case QUEER_IOTA:
        translit_table = iota_translit_table;
        translit_table_size = iota_translit_table_size;
        break;

    case I_IOTA:
        translit_table = i_iota_translit_table;
        translit_table_size = i_iota_translit_table_size;
        break;

    case I_SOFT:
        translit_table = i_soft_translit_table;
        translit_table_size = i_soft_translit_table_size;
        break;

    case HARD_SIGN:
        return;

    default:
        fputwc(curr_char, outfile);
        return;
    }

    const wchar_t *lat_char = translit_char(curr_char, translit_table, translit_table_size);
    fputws(lat_char, outfile);
};
