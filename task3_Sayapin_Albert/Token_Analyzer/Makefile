all : 
	g++ -Wall -pedantic -I ../Library/source/ -I ../Library/headers/ -I ./headers/ -I ./source/ ../Library/source/Token.cpp ../Library/source/Analyzer.cpp ../Library/source/paint_string.cpp ./source/Painter.cpp ../Library/headers/Counter.h ./source/TokenCounter.cpp ./source/main.cpp -o analyzer
cov_debug :
	g++ -Wall -pedantic -I ../Library/ -g --coverage -I ../Library/source/ -I ../Library/headers/ -I ./headers/ -I ./source/ ../Library/source/Token.cpp ../Library/source/Analyzer.cpp ../Library/source/paint_string.cpp ./source/Painter.cpp ../Library/headers/Counter.h ./source/TokenCounter.cpp ./source/main.cpp -o analyzer


clean :
	rm -f *.gc*
