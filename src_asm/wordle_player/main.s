# Main ASM_WordlePlayer function
.data
.text
.global main
main:
    call word_dict__init
    call wordle_player__reset
    call _exit
