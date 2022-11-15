.data
    target_word_index: .space 4

# Description:
#     Resets the wordle game and picks a new random word.
# Usage:
#     call wordle_game__reset
.data
    l_rnd: .space 4
.text
.global wordle_game__reset
wordle_game__reset:
    # Throw error if dictionary is not initialized
    call word_dict__throw_if_uninitialized

    # Get random dictionary index
    call _getrandom
    popl l_rnd
    
    ## Begin register block
        pushal
        movl l_rnd, %eax
        movl word_dict__size, %ecx
        
        cdq # expand %eax -> %edx:%eax
        idiv %ecx
        
        mov %edx, target_word_index
        popal
    ## End register block
    
    # Make index positive if it's less than 0
    pushl target_word_index
    call math__abs
    popl target_word_index
    
    # Function footer
    ret

# Description:
#     Resets the wordle game and sets the word to a specified one.
# Usage:
#     pushl [forced_word_index]
#     call wordle_game__reset_forced_word
.data
    ERR_MSG: .asciz "Indexul specificat este in afara dictionarului"

    _rip: .space 4
    p_fwordidx: .space 4
.text
.global wordle_game__reset_forced_word
wordle_game__reset_forced_word:
    # Function header
    popl _rip
    popl p_fwordidx
    
    # Throw error if dictionary is not initialized
    call word_dict__throw_if_uninitialized
    
    ## Begin register block: %eax
        pushal
        movl p_fwordidx, %eax

        # Throw error if index is outside of dictionary
        cmpl word_dict__size, %eax
        jae wordle_game__reset_forced_word__if_outside
            pushl $ERR_MSG
            call _stderr
            call _exit
        wordle_game__reset_forced_word__if_outside:
    
        mov %eax, target_word_index
        popal
    ## End register block
    
    # Function footer
    pushl _rip
    ret

# Description:
#     Returns the current target word.
# Usage:
#     call wordle_game__get_target
#     popl *[target_word]
.data
    _rip_2: .space 4
    r_word: .space 4
.text
.global wordle_game__get_target
wordle_game__get_target:
    # Function header
    popl _rip_2
    
    # Throw error if dictionary is not initialized
    call word_dict__throw_if_uninitialized

    ## Begin register block: %eax, %ecx, %edx
        pushal
        movl $word_dict__list, %eax
        movl target_word_index, %ecx
        movl $6, %edx

        # Return pointer offset by target word index
        wordle_game__get_target_forr:
            addl %ecx, %eax
            sub $1, %edx
            cmpl $0, %edx
            ja wordle_game__get_target_forr

        movl %eax, r_word
        popal
    ## End register block

    # Function footer
    pushl r_word
    pushl _rip_2
    ret

# Description:
#     Applies a guess on the target word and returns the resulting pattern.
# Usage:
#     pushl *[guess]
#     call wordle_game__guess
#     popl [pattern]
.data
    _rip_3: .space 4
    p_guess_3: .space 4
.text
.global wordle_game__guess
wordle_game_guess:
    # Function header
    popl _rip_3
    popl p_guess_3
    
    
    
    # Function footer
    pushl _rip_3
    ret
