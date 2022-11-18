# Description:
#     Converts a pattern from an array format (status) to an int format (code).
# Usage:
#     pushl *[status]
#     call patterns__encode_pattern
#     popl [code]
.data
    _rip: .space 4
    p_status: .space 4
    r_code: .long 0
.text
.global patterns__encode_pattern
patterns__encode_pattern:
    # Function header
    popl _rip
    popl p_status

    ## Begin register block: %eax, %ebx, %ecx
    pushal
        movl p_status, %ecx
        
        # sum += status[0] * 81
        movl $0, %eax
        movl $81, %ebx
        movb (%ecx), %al
        mull %ebx
        addl %eax, r_code
        
        # sum += status[1] * 27
        movl $0, %eax
        movl $27, %ebx
        movb 1(%ecx), %al
        mull %ebx
        addl %eax, r_code
        
        # sum += status[2] * 9
        movl $0, %eax
        movl $9, %ebx
        movb 2(%ecx), %al
        mull %ebx
        addl %eax, r_code
        
        # sum += status[3] * 3
        movl $0, %eax
        movl $3, %ebx
        movb 3(%ecx), %al
        mull %ebx
        addl %eax, r_code
        
        # sum += status[4]
        movl $0, %eax
        movb 4(%ecx), %al
        addl %eax, r_code
        
    popal
    ## End register block

    # Function footer
    pushl r_code
    pushl _rip
    ret

# Description:
#     Converts a pattern from an int format (code) to an array format (status).
# Usage:
#     pushl [code]
#     pushl *[status_buffer]
#     call patterns__decode_pattern
.data
    _rip_1: .space 4
    p_encoded_1: .space 4
    p_status_1: .space 4
.text
.global patterns__decode_pattern
patterns__decode_pattern:
    # Function header
    popl _rip_1
    popl p_status_1
    popl p_encoded_1
    
    ## Begin register block: %eax, %ebx, %ecx, %edx, %esi
    pushal
        movl p_encoded_1, %eax
        movl p_status_1, %esi
        
        # for (i = 5; i <= 1; i--)
        movl $5, %ecx
        L_decode:
            # status[i - 1] = code % 3
            movl $0, %edx
            movl $3, %ebx
            divl %ebx
            movb %dl, -1(%esi, %ecx, 1)
            loop L_decode
        
    popal
    ## End register block
    
    # Function footer
    pushl _rip_1
    ret

# Description:
#     Generates the pattern given the target word and the guessed word.
# Usage:
#     pushl *[target]
#     pushl *[guess]
#     call patterns__get_pattern
#     popl [code]
.data
    _rip_2: .space 4
    p_target_2: .space 4
    p_guess_2: .space 4
    l_litere_2: .space 26
    l_status_2: .space 5
    r_code_2: .long 0
.text
.global patterns__get_pattern
patterns__get_pattern:
    # Function header
    popl _rip_2
    popl p_guess_2
    popl p_target_2
    
    ## Begin register block: %eax, %ebx, %ecx, %edx, %esi, %edi
        pushal
    
        # Step 1: Create occurence array for all of the letters in the target
        movl p_target_2, %esi
        lea l_litere_2, %edi
        mov $5, %ecx
        L_get_1:
            movl $0, %eax
            movb -1(%esi, %ecx, 1), %al
            subb $65, %al # 65 = 'A'
            incb (%edi, %eax, 1)
            loop L_get_1
            
        # Step 2: Determine green letters
        movl p_target_2, %esi
        movl p_guess_2, %edi
        lea l_status_2, %ebx
        movl $5, %ecx
        L_get_2:
            movb -1(%esi, %ecx, 1), %al
            movb -1(%edi, %ecx, 1), %dl
            cmp %al, %dl
            jne L_get_2_end
            movb $1, -1(%ebx, %ecx, 1)
        L_get_2_end:
            loop L_get_2
        
        # Step 3: Determine yellow letters
        movl p_guess_2, %esi
        lea l_litere_2, %edi
        lea l_status_2, %ebx
        mov $5, %ecx
        L_get_3:
            movb -1(%ebx, %ecx, 1), %al
            cmp $0, %al # if (pattern[i] == GRAY
            jne L_get_3_end
            
            movl $0, %eax
            movb -1(%esi, %ecx, 1), %al
            sub $65, %al
            movb -1(%edi, %eax, 1), %dl
            cmp $0, %dl # && litere[guess[i] - 'A'] > 0)
            jle L_get_3_end
            
            movb $2, -1(%ebx, %ecx, 1)
        L_get_3_end:
            loop L_get_3
    
        popal
    ## End register block
    
    # Encode pattern to int format
    pushl $l_status_2
    call patterns__encode_pattern
    popl r_code_2
    
    # Function footer
    pushl r_code_2
    pushl _rip_2
    ret
