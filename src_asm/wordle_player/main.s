.data
    .global WP_NO_GUESSES
    WP_NO_GUESSES: .long 0 # Number of tried guesses
    .global WP_FIRST_GUESS
    WP_FIRST_GUESS: .ascii "TAREI"

# Main ASM_WordlePlayer function
.data
    newline: .asciz "\n"
    ohno: .asciz "~~~~~~~~~~\n"
    test_target: .space 4
    test_guess: .space 4
    test_pattern: .long 0
.text
.global main
main:
    call word_dict__init
    # TODO: Remove WordleGame dependency!

    # Test begin
    # 6046 MLAJI
    # pushl $6046
    # call wordle_game__reset_forced_word


    # Test end

    call _exit
