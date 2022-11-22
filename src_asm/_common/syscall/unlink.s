# Description:
#    Deletes a file.
# Usage:
#    pushl *[file_name]
#    call _unlink
.data
    _rip: .space 4
    file_name: .space 4
.text
.global _unlink
_unlink:
    popl _rip
    popl file_name

    pushal
        movl $0x0a, %eax
        movl file_name, %ebx
        int $0x80
    popal

    pushl _rip
    ret
