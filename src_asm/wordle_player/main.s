.data
    .global WP_NO_GUESSES
    WP_NO_GUESSES: .long 0 # Number of tried guesses
    .global WP_FIRST_GUESS
    WP_FIRST_GUESS: .ascii "TAREI"

# Main ASM_WordlePlayer function
.data
    newline: .asciz "\n"
    buffer: .space 12
    test_guess: .space 4
    test_pattern: .long 0
    str_guess: .asciz "[Guess]: "
    str_received: .asciz "[Received]: "
    file_send: .asciz "wp_data.txt"
    file_send_s: .asciz "wp_done.txt"
    file_receive: .asciz "wg_data.txt"
    file_receive_s: .asciz "wg_done.txt"
    fd_1: .space 4
.text
.global main
main:
    # TODO: Remove WordleGame dependency!

    # Test begin
    # 6046 MLAJI
    # pushl $6046
    # call wordle_game__reset_forced_word

    call word_dict__init
    call wordle_player__reset

    test_loop:
        # Get best guess
        call wordle_player__get_best_guess
        popl test_guess

        # Write to console the best guess
        pushl $str_guess
        call _stdout
        pushl test_guess
        pushl $5
        call _stdout_sz
        pushl $newline
        pushl $1
        call _stdout_sz

        # Write to $file_send the guess
        pushl $file_send
        call _open_w
        popl fd_1

        pushl fd_1
        pushl test_guess
        pushl $5
        call _write_sz

        pushl fd_1
        pushl $newline
        call _write

        # Close file
        pushl fd_1
        call _close

        # Signal WordleGame to read the guess
        pushl $file_send_s
        call _open_w
        popl fd_1

        pushl fd_1
        call _close

        # Wait for the pattern
        test_wait:
            pushl $file_receive_s
            call _access
            popl %eax
            cmp $0, %eax
            je test_wait

        # We are ready, delete the semaphore
        pushl $file_receive_s
        call _unlink

        # Read pattern
        pushl $file_receive
        call _open
        popl fd_1

        pushl fd_1
        pushl $buffer
        call _read_int
        popl test_pattern

        pushl fd_1
        call _close

        # Print received pattern to console
        pushl $str_received
        call _stdout
        pushl $1
        pushl test_pattern
        call _write_int

        # Test if we are done
        movl $121, %eax
        cmp test_pattern, %eax
        je test_loop_fin

        # Apply pattern
        pushl test_guess
        pushl test_pattern
        call wordle_player__apply_guess

        jmp test_loop

    test_loop_fin:

    call _exit
