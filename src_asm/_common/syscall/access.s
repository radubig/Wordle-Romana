# Description:
#     Check if a file can be opened (without oppening it first).
#     Returns 1 if the file can be opened or 0 otherwise.
# Usage:
#     pushl *[file]
#     call _access
#     popl status
.data
    _rip: .space 4
    a_file: .space 4
    status: .long 0
.text
.global _access
_access:
    popl _rip
    popl a_file
    movl $0, status
    pushal
       movl $0x21, %eax # 33 is syscall for access
       movl a_file, %ebx
       movl $0x0, %ecx # flag 0 tests if file exists
       int $0x80

       # the return value is stored in %eax
       # if %eax == 0 then the file exists
       cmp $0, %eax
       jne access_fin
       movl $1, status
       access_fin:

    popal
    pushl status
    pushl _rip
    ret
