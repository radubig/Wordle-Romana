.data
    .global word_dict__list
    word_dict__list: .space 70000
    .global word_dict__size
    word_dict__size: .long 0

# Description:
#     Initializes the wordle dictionary by reading from the word dictionary file.
# Usage:
#     call wordle_dict__init
.data
    l_fd: .space 4
    l_length: .space 4
.text
.global wordle_dict__init
wordle_dict__init:
    # Open word dictionary
    pushl $WORD_DICTIONARY_FILE_PATH
    call _open
    popl l_fd
    
    # Read dictionary to end
    pushl l_fd
    pushl $word_dict__list
    pushl $70000
    call _read
    popl l_length
    
    ## Begin register block: %eax, %ecx, %edx
        pushal
        movl l_length, %eax
        
        # Calculate and store number of words
        movl $0, %edx
        add $2, %eax
        movl $6, %ecx
        div %ecx
    
        movl %eax, word_dict__size
        popal
    ## End register block
    
    ret

# Description:
#     Throws an error if the dictionary has not been intialized.
# Usage:
#     call word_dict__throw_if_uninitialized
.data
    ERR_NO_DICT: .asciz "Dictionarul nu a fost initializat"
.text
.global word_dict__throw_if_uninitialized
word_dict__throw_if_uninitialized:
    ## Begin register block: %eax
        pushal
        movl word_dict__size, %eax
    
        cmpl $0, %eax
        ja throw_err_if_no_dict__if
            pushl $ERR_NO_DICT
            call _stderr
            call _exit
        throw_err_if_no_dict__if:
    
        popal
    ## End register block
    
    # Function footer
    ret

# Description:
#     Check if the given word is in the dictionary.
# Usage:
#     pushl *[word]
#     call word_dict__check
#     popl [result]
.data
    _rip: .space 4
    p_word: .space 4
    r_result: .space 4
.text
.global word_dict__check
word_dict__check:
    # Function header
    popl _rip
    popl p_word
    
    
    
    # Function footer
    pushl r_result
    pushl _rip
    ret