mastermind: mastermind.c
	gcc -o mastermind mastermind.c -Wall -Wextra -Werror -g3 -fsanitize=address

clean:
	shred -fzun 3 mastermind
