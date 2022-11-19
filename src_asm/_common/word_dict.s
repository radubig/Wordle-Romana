.data
    .global word_dict__list
    word_dict__list: .space 70000
    .global word_dict__size
    word_dict__size: .long 0
    # TODO: mtop (scope)
    # word_dict_remaining este un vector de frecventa
    .global word_dict__remaining
    word_dict__remaining: .space 15000
    .global word_dict__remaining_size
    word_dict__remaining_size: .long 0

# Description:
#     Initializes the wordle dictionary by reading from the word dictionary file.
# Usage:
#     call word_dict__init
.data
    l_fd: .space 4
    l_length: .space 4
.text
.global word_dict__init
word_dict__init:
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
    
    ## Begin register block: %eax, %ecx, %edx, %esi
        pushal
        movl l_length, %eax
        
        # Calculate and store number of words
        movl $0, %edx
        add $2, %eax
        movl $6, %ecx
        div %ecx
    
        movl %eax, word_dict__size

        # Initialize all elements of word_dict__remaining to 1
        # %eax still holds word_dict__size value
        movl %eax, %ecx
        lea word_dict__remaining, %esi
        L_init:
            movb $1, -1(%esi, %ecx, 1)
            loop L_init
        movl %eax, word_dict__remaining_size

        popal
    ## End register block
    
    # Function footer
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
        ja B_err
            pushl $ERR_NO_DICT
            call _stderr
            call _exit
        B_err:
    
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
    r_result: .long 0
.text
.global word_dict__check
word_dict__check:
    # Function header
    popl _rip
    popl p_word
    
    ## Begin register block: %eax, %ebx, %ecx, %edx
        pushal
        movl $word_dict__list, %ebx
        movl word_dict__size, %ecx
        movl $0, %eax
        
        # Check every word in the dictionary
        L_check:
            # Because we have no way of comparing strings, we can use patterns__get_pattern to check them instead xD
            # This is so scuffed but I love it!
            pushl (%ebx, %eax, 1)
            pushl p_word
            call patterns__get_pattern
            popl %edx
            
            cmpl $121, %edx
            je B_ok
            
            add $6, %eax
            loop L_check
    
        jmp B_not_ok
        B_ok:
            movl $0xffffffff, r_result
        B_not_ok:
        popal
    ## End register block
    
    # Function footer
    pushl r_result
    pushl _rip
    ret
