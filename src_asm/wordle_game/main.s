.data
    INTRO_TEXT: .asciz "Wordle: Incearca sa ghicesti un cuvant de 5 litere!\nVei primi la fiecare incercare indicatii despre ce litere fac parte din cuvant.\n\nEsti pregatit? Tasteaza un cuvant de 5 litere:\n";
    NOT_5_CHARS: .asciz "Cuvantul introdus nu are 5 litere!\nIntrodu un alt cuvant:\n"
    
    A_LOWER: .ascii "a"
    Z_LOWER: .ascii "z"
    
    pattern_code: .byte 255
    guesses: .long 0
    guess: .space 10
.text

.global main
main:
    # initialize the dictionary and the game
    call wordle_dict__init
    call wordle_game__reset

    pushl $INTRO_TEXT
    call _stdout
    
        # read the guess
        pushl $guess
        pushl $7
        call _stdin
        popl %eax

        # display error if guess is not 5 characters        
        pushl $guess
        pushl $10
        call string__length_with_trim
        popl %eax
        cmpl $5, %eax
        je main__if_guess_size
            pushl $NOT_5_CHARS
            call _stdout
        main__if_guess_size:
        
        # make guess uppercase
        movl $0, %eax
        lea guess, %ebx
        main__for_char_1:
            movb (%ebx, %eax, 1), %cl
            
            cmpb A_LOWER, %cl
            jb main__if_char_not_lower
            cmpb Z_LOWER, %cl
            ja main__if_char_not_lower
                subb $32, %cl
            main__if_char_not_lower:
            
            movb %cl, (%ebx, %eax, 1)
            
            addl $1, %eax
            cmp $5, %eax
            jb main__for_char_1
            
        test:

    call _exit
