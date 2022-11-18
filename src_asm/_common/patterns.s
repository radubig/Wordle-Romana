# Description:
#   It's a pattern!
# Usage:
#   Assuming %esi has $_globl_status,
#   (%esi, %ecx, 1) represents status of letter[%ecx].
.data
    .global _globl_status
    _globl_status: .space 8

# Description:
#   Encodes Pattern into cov_v
# Usage:
#   call patterns__encode_pattern
#   popl cov_v # long
.data
    cov_v: .long 0
    sum: .long 0
    _rip: .space 4
.text
.global patterns__encode_pattern
patterns__encode_pattern:
    popl _rip
    pushal # begin reg block

    lea _globl_status, %esi
    xor %ecx, %ecx
    # status[0] * 81
    xor %eax, %eax
    movb (%esi, %ecx, 1), %al
    mov $81, %ebx
    mul %ebx
    add %eax, sum
    inc %ecx

    # status[1] * 27
    xor %eax, %eax
    movb (%esi, %ecx, 1), %al
    mov $27, %ebx
    mul %ebx
    add %eax, sum
    inc %ecx

    # status[2] * 9
    xor %eax, %eax
    movb (%esi, %ecx, 1), %al
    mov $9, %ebx
    mul %ebx
    add %eax, sum
    inc %ecx

    # status[3] * 3
    xor %eax, %eax
    movb (%esi, %ecx, 1), %al
    mov $3, %ebx
    mul %ebx
    add %eax, sum
    inc %ecx

    # status[4] * 1
    xor %eax, %eax
    movb (%esi, %ecx, 1), %al
    add %eax, sum

    # move result
    movl sum, %eax
    movl %eax, cov_v

    popal # end reg block

    pushl cov_v
    pushl _rip
    ret


# Description:
#   Decodes Pattern from cov_v
# Usage:
#   pushl cov_v
#   call patterns__decode_pattern
.data
    _rip: .space 4
    cov_v: .space 4
.text
.global patterns__decode_pattern
patterns__decode_pattern:
    popl _rip
    popl cov_v

    pushal # Begin reg block
        lea _globl_status, %esi
        mov $5, %ecx
        movl cov_v, %eax

        #iterez de la ecx = 5 ... 1
        mov $5, %ecx
        L_1:
            xor %edx, %edx
            mov $3, %ebx
            div %ebx
            movb %dl, -1(%esi, %ecx, 1) #v[ecx - 1] = rest
            loop L_1

    popal # End reg block
    pushl _rip
    ret


# Description:
#   Sets all elements of Pattern to 0.
# Usage:
#   call patterns__clear_pattern
.data
.text
.global patterns__clear_pattern
patterns__clear_pattern:
    pushal
    lea _globl_status, %esi
    movl $0, 0(%esi)
    movl $0, 4(%esi)
    popal
    ret
