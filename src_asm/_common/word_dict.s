.data
    .global wordle_dict__dictionary
    wordle_dict__dictionary: .space 70000
    .global wordle_dict__size
    wordle_dict__size: .long 0
.text

# Description:
#     Initializes the wordle dictionary by reading from the word dictionary file.
# Usage:
#     call wordle_dict__init
.global wordle_dict__init
wordle_dict__init:
    # open word dictionary
    pushl $WORD_DICTIONARY_FILE_PATH
    call _open
    
    # read dictionary to end
    pushl $wordle_dict__dictionary
    pushl $70000
    call _read
    popl %eax
    
    # calculate and store number of words
    movl $0, %edx
    add $2, %eax
    movl $6, %ecx
    div %ecx
    movl %eax, wordle_dict__size
    
    ret
