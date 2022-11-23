.data
    NOT_5_CHARS: .asciz "Cuvantul introdus nu are 5 litere!\nIntrodu un alt cuvant:\n"
    
    newline: .asciz "\n"
    test_target: .space 4
    test_guess: .zero 8
    test_pattern: .long 0
    file_receive: .asciz "wp_data.txt"
    file_receive_s: .asciz "wp_done.txt"
    file_send: .asciz "wg_data.txt"
    file_send_s: .asciz "wg_done.txt"
    fd_1: .space 4
    str_received: .asciz "[Received]: "
    str_pattern: .asciz "[Pattern]: "

.text
.global main
main:
    call word_dict__init
    call wordle_game__reset

    call wordle_game__get_target
    popl test_target
    /*
    pushl test_target
    pushl $6
    call _stdout_sz
    */

    test_loop:
        # Wait to read guess
        test_wait:
            pushl $file_receive_s
            call _access
            popl %eax
            cmp $0, %eax
            je test_wait

        # We are ready to read guess, remove the semaphore
        pushl $file_receive_s
        call _unlink

        # Read guess
        pushl $file_receive
        call _open
        popl fd_1

        pushl fd_1
        pushl $test_guess
        pushl $5
        call _read
        popl %eax # Garbage

        pushl fd_1
        call _close

        # Print the received guess to console
        pushl $str_received
        call _stdout
        pushl $test_guess
        pushl $5
        call _stdout_sz
        pushl $newline
        call _stdout

        # Calculate pattern
        pushl $test_guess
        call wordle_game__guess
        popl test_pattern

        # Print the pattern to console
        pushl $str_pattern
        call _stdout
        pushl $1
        pushl test_pattern
        call _write_int

        # Send the pattern to file
        pushl $file_send
        call _open_w
        popl fd_1

        pushl fd_1
        pushl test_pattern
        call _write_int

        pushl fd_1
        call _close

        # Set the semaphore
        pushl $file_send_s
        call _open_w
        popl fd_1

        pushl fd_1
        call _close

        # Check if the game is finished
        mov $121, %eax
        cmp test_pattern, %eax
        je test_loop_fin

        jmp test_loop

    test_loop_fin:
    call _exit
