# Description:
#     Clears all patterns from the fuction under this.
# Usage:
#     pushl *[patterns]
#     call entropy__clear_patterns
.data
    _rip_1: .space 4
    p_patterns_1: .space 4
.text
entropy__clear_patterns:
    # Function header
    popl _rip_1
    popl p_patterns_1
    
    # Begin reg block
        pushal
        mov p_patterns_1, %esi
        mov $243, %ecx
        L_clear:
            movl $0, -4(%esi, %ecx, 4)
            loop L_clear
        popal
    # End reg block
    
    # Function footer
    pushl _rip_1
    ret

# Description:
#     Calculates best word based on entropy.
#     Input: dictionary and remaining_words.
#     Output: best word (as char[5])
# Usage:
#     pushl *[dictionary]
#     pushl *[dictionary_sz]
#     pushl *[remaining_words]
#     pushl *[remaining_words_sz]
#     call entropy__calculate_entropy
#     popl *[best_word]
.data
    _rip: .space 4
    e_dict: .space 4
    e_dict_sz: .space 4
    e_cuvram: .space 4
    e_cuvram_sz: .space 4

    mx_string: .space 5
    mx_entropy: .float 0

    e_patterns: .space 1000
    #NUM_PATTERNS = 243
    e_current_guess: .space 5
    e_current_target: .space 5
    e_cod_p: .long 0
    e_ent: .float 0
    e_p: .float 0
    e_v: .float 0
    e_aux: .long 0

.text
.globl entropy__calculate_entropy
entropy__calculate_entropy:
    popl _rip
    popl e_cuvram_sz
    popl e_cuvram
    popl e_dict_sz
    popl e_dict

    fldz
    fstps mx_entropy

    ## Begin reg block
    pushal
        # Iterate over all words from e_dict
        mov e_dict_sz, %ecx
        xorl %eax, %eax
        FOR_EACH_GUESS_FROM_DICT:

            # retrieve current guess
            mov e_dict, %esi
            lea e_current_guess, %edi
            movl (%esi, %eax, 1), %ebx
            movl %ebx, 0(%edi)
            movb 4(%esi, %eax, 1), %bl
            movb %bl, 4(%edi)

            # patterns[] = {0}
            pushl $e_patterns
            call entropy__clear_patterns

            ## Begin Reg Block
            pushal
                mov e_dict_sz, %ecx
                xorl %eax, %eax
                xorl %edx, %edx
                FOR_EACH_TARGET_FROM_REM_WORDS:
                    # test if target is still remaining
                    mov e_cuvram, %esi
                    movb (%esi, %edx, 1), %bl
                    cmp $1, %bl
                    jne FOR_EACH_TARGET_FROM_REM_WORDS__fin

                    # retrieve current target
                    lea e_current_target, %edi
                    mov e_dict, %esi
                    movl (%esi, %eax, 1), %ebx
                    movl %ebx, 0(%edi)
                    movb 4(%esi, %eax, 1), %bl
                    movb %bl, 4(%edi)

                    # Get the pattern code
                    pushl $e_current_target
                    pushl $e_current_guess
                    call patterns__get_pattern
                    popl e_cod_p

                    # patterns[cod_p]++;
                    # *(patterns + 4 * e_cod_p)++
                    movl e_cod_p, %ebx
                    lea e_patterns, %esi
                    incl (%esi, %ebx, 4)

                FOR_EACH_TARGET_FROM_REM_WORDS__fin:
                    addl $6, %eax
                    incl %edx
                    loop FOR_EACH_TARGET_FROM_REM_WORDS
            popal
            ## End reg block

            # De aici incepe partea cu calcularea entropiei, doamne ajuta
            pushal
                fldz # incarca +0.0f pe stiva
                fstps e_ent # descarca val de pe stiva in e_ent si da pop
                # for(int pattern : patterns)
                mov $243, %ecx
                mov $e_patterns, %esi
                FOR_ALL_PATTERNS:
                    # Retrieve the number of matches in e_aux
                    movl -4(%esi, %ecx, 4), %eax
                    movl %eax, e_aux

                    # double p = 1.0 * pattern / cuvinteRamase.size();
                    fildl e_cuvram_sz
                    fildl e_aux
                    fdivp %st, %st(1)
                    fsts e_p
                    ## in momentul acesta pe st[0] se afla p

                    # if (p == 0) continue;
                    fldz
                    fcomip #echivalentul lui cmp + un pop
                    fstp %st #golesc stiva de tot
                    je FOR_ALL_PATTERNS__fin

                    # double v = p * log2(1.0 / p);
                    flds e_p
                    fld1
                    fdivp %st, %st(1)
                    fstps e_v

                    fld1
                    flds e_v
                    fyl2x
                    fmuls e_p

                    # entropy += v
                    fadds e_ent
                    fstps e_ent

                FOR_ALL_PATTERNS__fin:
                    loop FOR_ALL_PATTERNS
            popal
            # Doamne ajuta

            # Update mx_string
            # fcomip face ultimul ? primul
            flds mx_entropy
            flds e_ent
            fcomip
            fstp %st
            jbe FOR_EACH_GUESS_FROM_DICT__fin

            # Update max
            flds e_ent
            fstps mx_entropy
            lea e_current_guess, %esi
            lea mx_string, %edi
            movl 0(%esi), %ebx
            movl %ebx, 0(%edi)
            movb 4(%esi), %bl
            movb %bl, 4(%edi)

        FOR_EACH_GUESS_FROM_DICT__fin:
            addl $6, %eax
            decl %ecx
            cmp $0, %ecx
            je FOR_EXIT_1
            jmp FOR_EACH_GUESS_FROM_DICT
        FOR_EXIT_1:

    popal
    ## End reg block
    pushl $mx_string
    pushl _rip
    ret
