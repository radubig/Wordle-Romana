.data

.text

.global main
main:
    call wordle_dict__init
    call wordle_game__reset

    call _exit
