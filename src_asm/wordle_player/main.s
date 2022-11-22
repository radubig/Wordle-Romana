.data
    .global WP_NO_GUESSES
    WP_NO_GUESSES: .long 0 # Number of tried guesses
    .global WP_FIRST_GUESS
    WP_FIRST_GUESS: .ascii "TAREI"

# Main ASM_WordlePlayer function
.data
    newline: .asciz "\n"
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

        call wordle_game__reset

        call wordle_game__get_target
        popl test_target
        pushl test_target
        pushl $6
        call _stdout_sz

        call wordle_player__reset

        test_loop:
            # Get best guess
            call wordle_player__get_best_guess
            popl test_guess

            pushl test_guess
            pushl $5
            call _stdout_sz
            pushl $newline
            pushl $1
            call _stdout_sz

            pushl test_guess
            call wordle_game__guess
            popl test_pattern

            movl $121, %eax
            cmp test_pattern, %eax
            je test_loop_fin

            pushl test_guess
            pushl test_pattern
            call wordle_player__apply_guess

            jmp test_loop

        test_loop_fin:

        call _exit


    # Test end

    call _exit
