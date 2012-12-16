compressor: compressor.o compressor.class.o
	g++ -o compressor compressor.o compressor.class.o -lcrypto -lz

compressor.o: compressor.cpp
	g++ -c compressor.cpp
	
compressor.class.o: ../compressor.class.cpp
	g++ -c ../compressor.class.cpp
