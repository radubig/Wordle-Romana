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
