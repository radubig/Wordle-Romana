.data
    INTRO_TEXT: .asciz "Wordle: Incearca sa ghicesti un cuvant de 5 litere!\nVei primi la fiecare incercare indicatii despre ce litere fac parte din cuvant.\n\nEsti pregatit? Tasteaza un cuvant de 5 litere:\n";
    NOT_5_CHARS: .asciz "Cuvantul introdus nu are 5 litere!\nIntrodu un alt cuvant:\n"
    
    pattern_code: .byte 255
    guesses: .long 0

    l_guess: .space 10
    l_inputlen: .space 4
    
    test_file: .asciz "cuvinte.txt"
    test_bun: .asciz "Fisierul exista!\n"
    test_rau: .asciz "Fisierul NU exista!\n"

.text
.global main
main:
    # Initialize the dictionary and the game
    call word_dict__init

    # Test access

    pushl $test_file
    call _access
    popl %eax

    cmp $1, %eax
    jne nu_exista
    pushl $test_bun
    call _stdout
    jmp b_end
    nu_exista:
    pushl $test_rau
    call _stdout

    b_end:
    call _exit

    # End of test

    # Display the intro text
    pushl $INTRO_TEXT
    call _stdout
    
    # TODO: Add some kinda loop here
        # Read the guess
        pushl $l_guess
        pushl $10
        call _stdin
        popl %eax # discard

        # Calculate length of guess    
        pushl $l_guess
        pushl $10
        call string__length_with_trim
        popl l_inputlen
        
        # Throw an error if guess is not 5 characters
        # TODO: This is useless (read todo.txt)
        cmpl $5, l_inputlen
        je et_len
            pushl $NOT_5_CHARS
            call _stdout
        et_len:
        
        # Make guess uppercase
        pushl $l_guess
        call string__to_upper

    call _exit
