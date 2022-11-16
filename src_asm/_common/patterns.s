# Description:
#   It's a pattern!
# Usage:
#   Assuming %esi has $_globl_status,
#   (%esi, %ecx, 1) represents status of letter[%ecx].
.data
    .global _globl_status
    _globl_status: .space 8

# Description:
#   Decodes Pattern.
# Usage:
#   call patterns__encode_pattern
#   popl cov_v # long
.data
    cov_v: .long 0
    sum: .long 0
.text
.global patterns__encode_pattern
patterns__encode_pattern:
    pusha # begin reg block

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

    popa # end reg block

    pushl cov_v
    ret
