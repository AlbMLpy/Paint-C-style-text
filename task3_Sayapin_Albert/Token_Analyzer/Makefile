all : 
	g++ -Wall -pedantic -I ../Library/ ../Library/Dynamic_Vec.cpp ../Library/Token.cpp ../Library/Define_Token.cpp ../Library/Painter.cpp ../Library/Counter.cpp ../Library/Counter_Token.cpp ../Library/polymorph_action_tokens.cpp main.cpp -o analyzer
cov_debug :
	g++ -Wall -pedantic -I ../Library/ -g --coverage ../Library/Dynamic_Vec.cpp ../Library/Token.cpp ../Library/Define_Token.cpp ../Library/Painter.cpp ../Library/Counter.cpp ../Library/Counter_Token.cpp ../Library/polymorph_action_tokens.cpp main.cpp -o analyzer
clean :
	rm -f *.gc*
