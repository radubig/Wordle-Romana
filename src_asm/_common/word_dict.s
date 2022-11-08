.data

.global dictionary
dictionary: .space 70000

.text

.global wordle_dict__init
wordle_dict__init:
    pushl $WORD_DICTIONARY_FILE_PATH
    call _open
    
    pushl $dictionary
    pushl $70000
    call _read
    
    ret