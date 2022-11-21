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
