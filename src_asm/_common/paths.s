.data
    WORD_DICTIONARY_FILE_PATH: .asciz "cuvinte.txt"

.text

.global get_WORD_DICTIONARY_FILE_PATH
get_WORD_DICTIONARY_FILE_PATH:
    popl %edx
    pushl $WORD_DICTIONARY_FILE_PATH
    pushl %edx
    ret
