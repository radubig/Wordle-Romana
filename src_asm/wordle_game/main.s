.data
    INTRO_TEXT: .asciz "Wordle: Incearca sa ghicesti un cuvant de 5 litere!\nVei primi la fiecare incercare indicatii despre ce litere fac parte din cuvant.\n\nEsti pregatit? Tasteaza un cuvant de 5 litere:\n";
    NOT_5_CHARS: .asciz "Cuvantul introdus nu are 5 litere!\nIntrodu un alt cuvant:\n"
    
    pattern_code: .byte 255
    guesses: .long 0
.data
    l_guess: .space 10
    l_inputlen: .space 4
.text
.global main
main:
    # Initialize the dictionary and the game
    call wordle_dict__init
    call wordle_game__reset

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
        cmpl $5, l_inputlen
        je main__if_guess_size
            pushl $NOT_5_CHARS
            call _stdout
        main__if_guess_size:
        
        # Make guess uppercase
        pushl $l_guess
        call string__to_upper
        
        # TODO: Check if guess contains invalid characters
        
        test:

    call _exit
