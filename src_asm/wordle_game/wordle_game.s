.data
    ERR_NO_DICT: .asciz "Dictionarul nu a fost initializat inainte de resetarea jocului"

.text

.global wordle_game__reset
wordle_game__reset:
    movl wordle_dict__size, %eax
    movl $0, %ebx
    cmpl %ebx, %eax
    ja wordle_game__reset__if_no_dict
        pushl $ERR_NO_DICT
        call _stderr
        
        call _exit
    wordle_game__reset__if_no_dict:

    call _getrandom
    popl %eax
    cdq
    # TODO: idiv to get remainder, maths.abs and store in variable
    