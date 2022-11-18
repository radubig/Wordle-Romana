# Description:
#     Converts a pattern from an array format to an int format.
#     The "status_left" parameter contains the status of the first 4 letters of the word, in order, and "status_right" contains the status of the last letter in the last byte.
# Usage:
#     pushb [status_left]
#     pushl [status_right]
#     call patterns__encode_pattern
#     popl [encoded]
.data
    _rip: .space 4
    p_statusleft: .space 4
    p_statusright: .space 4
    r_encoded: .long 0
.text
.global patterns__encode_pattern
patterns__encode_pattern:
    # Function header
    popl _rip
    popl p_statusright
    popl p_statusleft

    ## Begin register block: %eax, %ebx, %ecx
        pushal
        lea p_statusleft, %ecx
        
        # sum += status[0] * 81
        movl $0, %eax
        movl $81, %ebx
        movb (%ecx), %al
        mull %ebx
        addl %eax, r_encoded
        
        # sum += status[1] * 27
        movl $0, %eax
        movl $27, %ebx
        movb 1(%ecx), %al
        mull %ebx
        addl %eax, r_encoded
        
        # sum += status[2] * 9
        movl $0, %eax
        movl $9, %ebx
        movb 2(%ecx), %al
        mull %ebx
        addl %eax, r_encoded
        
        # sum += status[3] * 3
        movl $0, %eax
        movl $3, %ebx
        movb 3(%ecx), %al
        mull %ebx
        addl %eax, r_encoded
        
        # sum += status[4]
        lea p_statusright, %ecx
        movl $0, %eax
        movb (%ecx), %al
        addl %eax, r_encoded
        
        popal
    ## End register block

    # Function footer
    pushl r_encoded
    pushl _rip
    ret

# Description:
#     Converts a pattern from an int format to an array format.
# Usage:
#     pushl [encoded]
#     call patterns__decode_pattern
#     popl [status_left]
#     popl [status_right]
.data
    _rip_1: .space 4
    p_encoded: .space 4
    r_statusleft: .long 0
    r_statusright: .long 0
.text
.global patterns__decode_pattern
patterns__decode_pattern:
    # Function header
    popl _rip_1
    popl p_encoded
    
    ## Begin register block: %eax, %ebx, %ecx, %edx
        pushal
        movl p_encoded, %eax
        
        movl $0, %edx
        movl $3, %ebx
        
        movl $5, %ecx
        patterns__decode_pattern__loop:
            movl $0, %edx
            movl $3, %ebx
            divl %ebx
            movb %dl, -1(%esi, %ecx, 1)
            
            loop patterns__decode_pattern__loop
        
        popal
    ## End register block
    
    # Function footer
    pushl r_statusright
    pushl r_statusleft
    pushl _rip_1
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
