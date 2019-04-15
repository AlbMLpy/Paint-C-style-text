all : 
	gcc -Wall -pedantic dynamic_vec.c dyn_vec_token.c define_token.c painter_container.c paint_tokens_in_file.c stat_on_num.c give_stats_tokens_in_file.c main.c -o analyzer
cov_debug :
	gcc -Wall -pedantic -g --coverage dynamic_vec.c dyn_vec_token.c define_token.c painter_container.c paint_tokens_in_file.c stat_on_num.c give_stats_tokens_in_file.c main.c -o analyzer
clean :
	rm -f *.gc*
