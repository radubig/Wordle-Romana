# Description:
#     Resets the list of remaining words.
# Usage:
#     Call wordle_player__reset
.data
.text
.global wordle_player__reset
wordle_player__reset:
    call word_dict__reset
    ret

# Description:
#     Returns the best guess
# Usage:
#     call wordle_player__get_best_guess
#     popl *[best_guess]
.data
    wp1_rip: .space 4
    wp1_best_guess: .space 4
.text
.global wordle_player__get_best_guess
wordle_player__get_best_guess:
    popl wp1_rip

    pushal
        # Check if this is the first guess
        movl WP_NO_GUESSES, %eax
        cmp $0, %eax
        jne wp1_L1
        movl $WP_FIRST_GUESS, %eax
        movl %eax, wp1_best_guess
        jmp wp1_END

    wp1_L1:
        # Check if the list has only one word
        movl word_dict__remaining_size, %eax
        cmp $1, %eax
        jne wp1_L2

        # If true then search said word
        movl word_dict__size, %ecx
        lea word_dict__remaining, %esi
        wp1_loop:
            movb -1(%esi, %ecx, 1), %al
            cmp $1, %al
            je wp1_loop_end
            loop wp1_loop
        wp1_loop_end:
        # Indexul se afla in %ecx - 1
        decl %ecx
        lea word_dict__list, %esi
        lea (%esi, %ecx, 4), %eax
        movl %eax, wp1_best_guess
        jmp wp1_END

    wp1_L2:
        # Calculeaza best guess pe baza entropiei
        pushl $word_dict__list
        pushl word_dict__size
        pushl $word_dict__remaining
        pushl word_dict__remaining_size
        call entropy__calculate_entropy
        popl wp1_best_guess

wp1_END:
    popal

    pushl wp1_best_guess
    pushl wp1_rip
    ret


# Description:
#     Checks if a word matches the pattern of a guess.
#     Returns 1 if the word matches the pattern or 0 otherwise.
# Usage:
#     pushl *[guess]
#     pushl *[pattern] (in byte format)
#     pushl *[word]
#     call wordle_player__check_guess
#     popl result (long)
.data
    wp2_rip: .space 4
    wp2_guess: .space 4
    wp2_pattern: .space 4
    wp2_word: .space 4
    wp2_result: .long 1
.text
.global wordle_player__check_guess
wordle_player__check_guess:
    popl wp2_rip
    popl wp2_word
    popl wp2_pattern
    popl wp2_guess

    pushal
        # 0 .. 4
        movl $0, %ecx
        wp2_loop:
            movl wp2_pattern, %esi
            movb (%esi, %ecx, 1), %al
            xorl %ebx, %ebx # %ebx contine litera guess[i]
            movl wp2_guess, %edi
            movb (%edi, %ecx, 1), %bl

            cmp $0, %al # Cazul 0 (gri)
            jne wp2_L1
            pushl wp2_word
            pushl %ebx
            call wordle_player__find_letter
            popl %edx
            cmp $0, %edx
            je wp2_loop_fin
            movl $0, wp2_result
            jmp wp2_exit

            wp2_L1:
            cmp $1, %al # Cazul 1 (verde)
            jne wp2_L2
            movl wp2_word, %edi
            movb (%edi, %ecx, 1), %dl
            cmp %bl, %dl
            je wp2_loop_fin
            movl $0, wp2_result
            jmp wp2_exit

            wp2_L2: # Cazul 2 (galben)
            movl wp2_word, %edi
            movb (%edi, %ecx, 1), %dl
            cmp %bl, %dl
            jne wp2_L2_2
            movl $0, wp2_result
            jmp wp2_exit
            wp2_L2_2:
            pushl wp2_word
            pushl %ebx
            call wordle_player__find_letter
            popl %edx
            cmp $1, %edx
            je wp2_loop_fin
            movl $0, wp2_result
            jmp wp2_exit

            wp2_loop_fin:
            incl %ecx
            cmp $4, %ecx
            jle wp2_loop

    wp2_exit:
    popal

    pushl wp2_result
    pushl wp2_rip
    ret



# Description:
#     Implements word.find(letter) and returns 1 or 0.
# Usage:
#     pushl *[word] (5 bytes)
#     pushl lit (long)
#     call wordle_player__find_letter
#     popl result (long)
.data
    wp3_rip: .space 4
    wp3_word: .space 4
    wp3_lit: .long 0
    wp3_res: .long 0
.text
.global wordle_player__find_letter
wordle_player__find_letter:
    popl wp3_rip
    popl wp3_lit
    popl wp3_word
    pushal
        mov wp3_word, %esi
        mov $5, %ecx
        xorl %eax, %eax
        wp3_loop:
            movb -1(%esi, %ecx, 1), %al
            cmp wp3_lit, %eax
            je wp3_found
            loop wp3_loop
            jmp wp3_exit
        wp3_found:
        movl $1, wp3_res
        wp3_exit:

    popal
    pushl wp3_res
    pushl wp3_rip
    ret



# Description:
#     Updates remaining words based on the guessed word and the pattern code.
# Usage:
#     pushl *[guess]
#     pushl p_code (long)
#     call wordle_player__apply_guess
.data
    wp4_rip: .space 4
    wp4_guess: .space 4
    wp4_pcode: .long 0

    wp4_pattern: .space 5
.text
.global wordle_player__apply_guess
wordle_player__aply_guess:
    popl wp4_rip
    popl wp4_pcode
    popl wp4_guess

    pushl wp4_pcode
    pushl $wp4_pattern
    call patterns__decode_pattern

    # Begin reg block
    pushal
        xorl %eax, %eax
        xorl %ecx, %ecx
        lea word_dict__remaining, %esi
        lea word_dict__list, %edi

        wp4_loop:
            # Verify that word_dict__remaining still has %ecx
            movb (%esi, %ecx, 1), %bl
            cmp $0, %bl
            je wp4_loop_fin

            # Determine the address of the word and call function
            lea (%edi, %eax, 1), %ebx
            pushl wp4_guess
            pushl $wp4_pattern
            pushl %ebx
            call wordle_player__check_guess
            popl %ebx # result (1 or 0)

            cmp $1, %ebx
            je wp4_loop_fin

            # If 0 then remove said word
            movb $0, (%esi, %ecx, 1)
            decl word_dict__remaining_size

            wp4_loop_fin:
            incl %ecx
            addl $6, %eax
            cmp word_dict__size, %ecx
            jl wp4_loop

        incl WP_NO_GUESSES
        # TODO: May need to store the pattern code somewhere
    popal
    # End reg block

    pushl wp4_rip
    ret
