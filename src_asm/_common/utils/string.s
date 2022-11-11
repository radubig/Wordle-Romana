.data
    FIRST_GOOD_CHAR: .ascii "!"
    LAST_GOOD_CHAR: .ascii "~"

.text

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
    rip: .space 4
    r_string: .space 4
    r_maxlength: .space 4
    r_length: .long 0
.text
.global string__length_with_max
string__length_with_max:
    # Function header
    popl rip
    popl r_maxlength
    popl r_string

    popl %eax # rip
    popl %ebx # max_length
    popl %ecx # string
    
    ## Begin register block: %eax, %ebx, %ecx
        pushal
        movl r_length, %eax
        movl r_maxlength, %ebx
        movl r_string, %ecx
        string__length__loop:
            addl $1, %eax
            cmpl r_maxlength, %eax
            jae string__length__loop_end
            cmpb $0, (%ecx, %eax, 1)
            jne string__length__loop
        string__length__loop_end:
        movl %eax, r_length
        popal
    ## End register block

    # Function footer
    pushl r_length
    pushl rip
    ret

# Description:
#     Calculates and returns the length of a string.
#     This function uses the null terminator to find the end of the string.
#     The null terminator character is included in the returned length.
# Usage:
#     pushl *[string]
#     call string__length
#     popl [length]
.global string__length
string__length:
    popl %eax # rip
    pushl $0xffffffff
    pushl %eax
    jmp string__length_with_max

# Description:
#     Calculates and returns the length of a string up to a specified maximum, while excluding all weird characters (and spaces) from the end.
#     The null terminator is not included in the returned length.
# Usage:
#     pushl *[string]
#     pushl [max_length]
#     call string__length_with_trim
#     popl [length]
.global string__length_with_trim
string__length_with_trim:
    popl %eax # rip
    popl %ecx # max_length
    popl %ebx # string
    
    pushl %ebx
    pushl %ecx
    call string__length_with_max
    popl %ecx
    
    pushl %eax # free up eax register
    
    movb FIRST_GOOD_CHAR, %ah
    movb LAST_GOOD_CHAR, %al
    string__length_with_trim__forr:
        cmpb %ah, (%ebx, %ecx, 1)
        jae string__length_with_trim__good_char_1
            subl $1, %ecx
            jmp string__length_with_trim__forr
        string__length_with_trim__good_char_1:
        
        cmpb %al, (%ebx, %ecx, 1)
        jbe string__length_with_trim__good_char_2
            subl $1, %ecx
            jmp string__length_with_trim__forr
        string__length_with_trim__good_char_2:

    popl %eax # rip
    pushl %ecx # length
    pushl %eax
    ret
