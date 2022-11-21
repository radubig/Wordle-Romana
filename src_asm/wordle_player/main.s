.data
    .global WP_NO_GUESSES
    WP_NO_GUESSES: .long 0 # Number of tried guesses
    .global WP_FIRST_GUESS
    WP_FIRST_GUESS: .ascii "TAREI"

# Main ASM_WordlePlayer function
.data
.text
.global main
main:
    call word_dict__init
    call wordle_player__reset
    call _exit
