all : 
	g++ -Wall -pedantic -I ../Library/source/ -I ../Library/headers/ -I . ../Library/source/Token.cpp ../Library/source/Analyzer.cpp ../Library/source/paint_string.cpp ../Library/source/Painter.cpp ../Library/headers/Counter.h ../Library/source/TokenCounter.cpp main.cpp -o analyzer
cov_debug :
	g++ -Wall -pedantic -I ../Library/ -g --coverage -I ../Library/source/ -I ../Library/headers/ -I . ../Library/source/Token.cpp ../Library/source/Analyzer.cpp ../Library/source/paint_string.cpp ../Library/source/Painter.cpp ../Library/headers/Counter.h ../Library/source/TokenCounter.cpp main.cpp -o analyzer

clean :
	rm -f *.gc*
