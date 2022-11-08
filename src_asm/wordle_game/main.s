.data
    introStr: .asciz "Hello, World!"

.text

.extern _write
.extern _exit

.global main
main:
    pushl $introStr
    call _write

    call _exit
