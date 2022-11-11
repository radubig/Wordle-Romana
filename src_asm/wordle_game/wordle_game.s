.data
    ERR_NO_DICT: .asciz "Dictionarul nu a fost initializat inainte de resetarea jocului"
    target_word_index: .space 4
.text

# Description:
#     Resets the wordle game and picks a new random word.
# Usage:
#     call wordle_game__reset
.global wordle_game__reset
wordle_game__reset:
    call throw_err_if_no_dict

    # get random dictionary index
    call _getrandom
    popl %eax
    cdq # expand %eax -> %edx:%eax
    mov wordle_dict__size, %ecx
    idiv %ecx
    mov %edx, %ecx # get absolute value
    neg %edx
    cmovl %ecx, %edx
    mov %edx, target_word_index
    
    ret

# Description:
#     Resets the wordle game and sets the word to a specified one.
# Usage:
#     pushl [forced_word_index]
#     call wordle_game__reset_forced_word
.global wordle_game__reset_forced_word
wordle_game__reset_forced_word:
    call throw_err_if_no_dict
    popl target_word_index
    ret

# Description:
#     Returns the current target word.
# Usage:
#     call wordle_game__get_target
#     popl *[target_word]
.global wordle_game__get_target
wordle_game__get_target:
    # load dictionary pointer and offset by target word index
    movl $wordle_dict__dictionary, %eax
    movl target_word_index, %ecx
    mov $6, %edx
    wordle_game__get_target_forr:
        addl %ecx, %eax
        sub $1, %edx
        cmpl $0, %edx
        ja wordle_game__get_target_forr

    popl %edx
    pushl %eax
    pushl %edx
    ret

throw_err_if_no_dict:
    # throw error if dictionary is not initialized
    movl wordle_dict__size, %eax
    movl $0, %ebx
    cmpl %ebx, %eax
    ja throw_err_if_no_dict__if
        pushl $ERR_NO_DICT
        call _stderr
        
        call _exit
    throw_err_if_no_dict__if:
    
    ret
