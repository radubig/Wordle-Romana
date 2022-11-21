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
        movl *(%esi, %ecx, 4), %eax
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
