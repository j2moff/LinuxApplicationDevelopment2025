#ifndef DICT_H
#define DICT_H

#include <wchar.h>
#include <stdio.h>

/**
 * @struct char_type
 * @brief Type of a cyrillic character transliteration
 */
typedef enum {
    STRAIGHT,
    QUEER_SOFT,
    QUEER_IOTA,
    I_IOTA,
    I_SOFT,
    HARD_SIGN,
    ELSE
} char_type;

/**
 * @brief Get a cyrillic character transliteration type
 * @param curr_char Current cyrillic character
 * @param prev_char Previous cyrillic character
 * @result Cyrillic character transliteration type
 */
char_type get_char_type(wchar_t curr_char, wchar_t prev_char);

/**
 * @struct translit_pair
 * @brief Transliteration pair of a cyrillic character and corresponding latic characters
 */
typedef struct
{
    const wchar_t cyr_char;
    const wchar_t *lat_char;
} translit_pair;

/**
 * @brief Transliterate a cyrillic character according to some transliteration rules
 * @param curr_char Cyrillic character
 * @param translit_table Transliteration rules
 * @param translit_table_size Size of the `translit_table`
 * @return Corresponding latin characters
 */
const wchar_t* translit_char(wchar_t curr_char, const translit_pair *translit_table, const size_t translit_table_size);

/**
 * @brief Transliterate a cyrillic character and print the transliteration in some stream
 * @param curr_char Current cyrillic character
 * @param prev_char Previous cyrillic character
 * @param outfile Output stream
 */
void convert_and_print(wchar_t curr_char, wchar_t prev_char, FILE* outfile);

#endif
