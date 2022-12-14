# Description:
#     Calculates and returns the length of a string, up to the specified maximum length.
#     This function uses the null terminator to find the end of the string.
#     The null terminator is included in the returned length.
#     If the specified maximum length is reached, it will be returned without considering the null terminator character.
# Usage:
#     pushl *[string]
#     pushl [max_length]
#     call string__length_with_max
#     popl [length]
.data
    _rip: .space 4
    p_string: .space 4
    p_maxlength: .space 4
    r_length: .long 0
.text
.global string__length_with_max
string__length_with_max:
    # Function header
    popl _rip
    popl p_maxlength
    popl p_string

    ## Begin register block: %eax, %ebx, %ecx
        pushal
        movl $0, %eax
        movl p_maxlength, %ebx
        movl p_string, %ecx
        
        L_len:
            addl $1, %eax
            cmpl p_maxlength, %eax
            jae L_len_end
            cmpb $0, (%ecx, %eax, 1)
            jne L_len
        L_len_end:
        
        movl %eax, r_length
        popal
    ## End register block

    # Function footer
    pushl r_length # return value (length)
    pushl _rip
    ret

# Description:
#     Calculates and returns the length of a string.
#     This function uses the null terminator to find the end of the string.
#     The null terminator character is included in the returned length.
# Usage:
#     pushl *[string]
#     call string__length
#     popl [length]
.data
    _rip_2: .space 4
    p_string_2: .space 4
    r_length_2: .space 4
.text
.global string__length
string__length:
    # Function header
    popl _rip_2
    popl p_string_2

    # Call string__length_with_max with maximum int value as length parameter
    pushl p_string_2
    pushl $0xffffffff
    call string__length_with_max
    popl r_length_2

    # Function footer
    pushl r_length_2 # return value (length)
    pushl _rip_2
    ret

# Description:
#     Calculates and returns the length of a string up to a specified maximum, while excluding all weird characters (and spaces) from the end.
#     The null terminator is not included in the returned length.
# Usage:
#     pushl *[string]
#     pushl [max_length]
#     call string__length_with_trim
#     popl [length]
.data
    FIRST_GOOD_CHAR: .ascii "!"
    LAST_GOOD_CHAR: .ascii "~"
    _rip_3: .space 4
    p_string_3: .space 4
    p_maxlength_3: .space 4
    r_length_3: .space 4
.text
.global string__length_with_trim
string__length_with_trim:
    # Function header
    popl _rip_3
    popl p_maxlength_3
    popl p_string_3
    
    # Calculate the length of the string
    pushl p_string_3
    pushl p_maxlength_3
    call string__length_with_max
    popl r_length_3

    ## Begin register block: %eax, %ebx, %ecx
        pushal
        movb FIRST_GOOD_CHAR, %ah
        movb LAST_GOOD_CHAR, %al
        movl p_string_3, %ebx
        movl r_length_3, %ecx
        
        L_trim:
            cmpb %ah, -1(%ebx, %ecx, 1)
            jae B_trim_1
                subl $1, %ecx
                jmp L_trim
            B_trim_1:
        
            cmpb %al, -1(%ebx, %ecx, 1)
            jbe B_trim_2
                subl $1, %ecx
                jmp L_trim
            B_trim_2:
        
        movl %ecx, r_length_3
        popal
    ## End register block

    # Function footer
    pushl r_length_3 # return value (length)
    pushl _rip_3
    ret

# Description:
#     Converts the string into uppercase (in-place)
# Usage:
#     pushl *[string]
#     call string__to_upper
.data
    A_LOWER: .ascii "a"
    Z_LOWER: .ascii "z"
    _rip_4: .space 4
    p_string_4: .space 4
.text
.global string__to_upper
string__to_upper:
    # Function header
    popl _rip_4
    popl p_string_4
    
    ## Begin register block: %eax, %ebx, %ecx
        pushal
        movl $0, %eax
        movl p_string_4, %ebx
    
        L_upper:
            movb (%ebx, %eax, 1), %cl
            
            cmpb A_LOWER, %cl
            jb B_upper
            cmpb Z_LOWER, %cl
            ja B_upper
                subb $32, %cl
            B_upper:
            
            movb %cl, (%ebx, %eax, 1)
            
            addl $1, %eax
            cmp $5, %eax
            jb L_upper
        
        popal
    ## End register block
    
    # Function footer
    pushl _rip_4
    ret
