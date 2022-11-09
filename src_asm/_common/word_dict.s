.data
    .global wordle_dict__dictionary
    wordle_dict__dictionary: .space 70000
    .global wordle_dict__size
    wordle_dict__size: .long 0
.text

.global wordle_dict__init
wordle_dict__init:
    pushl $WORD_DICTIONARY_FILE_PATH
    call _open
    
    pushl $wordle_dict__dictionary
    pushl $70000
    call _read
    
    movl $0, %edx
    add $2, %eax
    movl $6, %ecx
    div %ecx
    movl %eax, wordle_dict__size
    
    ret
