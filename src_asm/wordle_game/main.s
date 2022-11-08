.text
.extern _exit
.extern _open
.extern _stdout
.extern get_WORD_DICTIONARY_FILE_PATH

.data

.text

.global main
main:
    call get_WORD_DICTIONARY_FILE_PATH
    call _open

    call _exit
