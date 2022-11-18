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
    _rip_1: .space 4
    cov_v_1: .space 4
.text
.global patterns__decode_pattern
patterns__decode_pattern:
    popl _rip_1
    popl cov_v_1

    pushal # Begin reg block
        lea _globl_status, %esi
        mov $5, %ecx
        movl cov_v_1, %eax

        #iterez de la ecx = 5 ... 1
        mov $5, %ecx
        L_1:
            xor %edx, %edx
            mov $3, %ebx
            div %ebx
            movb %dl, -1(%esi, %ecx, 1) #v[ecx - 1] = rest
            loop L_1

    popal # End reg block
    pushl _rip_1
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


# Description:
#   TBA
#   target and guess are considered to be of size char[5]
# Usage:
#   pushl *[target]
#   pushl *[guess]
#   call patterns__get_pattern
.data
    gp_rip: .space 4
    gp_guess: .space 4
    gp_target: .space 4
    litere: .zero 26
.text
.global patterns_get_pattern
patterns_get_pattern:
    popl gp_rip
    popl gp_guess
    popl gp_target

    ## Begin reg block
    pushal
        call patterns_clear_pattern

        # Pas 1
        lea gp_target, %esi
        lea litere, %edi
        mov $5, %ecx
        L_pas_1:
            movb -1(%esi, %ecx, 1), %al
            sub $65, %al
            incb (%edi, %al, 1)
            loop L_pas_1

        # Pas 2
        lea gp_target, %esi
        lea gp_guess, %edi
        lea _globl_status, %ebx
        mov $5, %ecx
        L_pas_2:
            movb -1(%esi, %ecx, 1), %al
            movb -1(%edi, %ecx, 1), %dl
            cmp %al, %dl
            jne L_pas_2_fin
            movb $1, -1(%ebx, %ecx, 1)
        L_pas_2_fin:
            loop L_pas_2

        # Pas 3
        # _globl_status e incarcat in %ebx
        lea gp_guess, %esi
        lea litere, %edi
        mov $5, %ecx
        L_pas_3:
            movb -1(%ebx, %ecx, 1), %al
            cmp $0, %al     # if(pattern[i] == GRAY
            jne L_pas_3_fin

            movb -1(%esi, %ecx, 1), %al
            sub $65, %al
            movb -1(%edi, %al, 1), %dl
            cmp $0, %dl     # && litere[guess[i] - 'A'] > 0 )
            jle L_pas_3_fin

            movb $2, -1(%ebx, %ecx, 1)

        L_pas_3_fin:
            loop L_pas_3

    popal
    ## End reg block
    pushl gp_rip
    ret
