extractor: ConnectedComponent.o PGMimageProcessor.o driver.o
	g++ ConnectedComponent.o PGMimageProcessor.o driver.o -o extractor -std=c++20

PGMimageProcessor.o: PGMimageProcessor.cpp
	g++ -c PGMimageProcessor.cpp -o PGMimageProcessor.o -std=c++20

ConnectedComponent.o: ConnectedComponent.cpp
	g++ -c ConnectedComponent.cpp -o ConnectedComponent.o -std=c++20
	
driver.o: driver.cpp
	g++ -c driver.cpp -o driver.o -std=c++20

TestComponent.o: TestComponent.cpp
	g++ -c TestComponent.cpp -o TestComponent.o -std=c++20

TestPGMimage.o: TestPGMimage.cpp
	g++ -c TestPGMimage.cpp -o TestPGMimage.o -std=c++20

run: TestComponent.o ConnectedComponent.o
	g++ TestComponent.o ConnectedComponent.o -o comp.exe -std=c++20

run1: TestPGMimage.o ConnectedComponent.o PGMimageProcessor.o
	g++ ConnectedComponent.o PGMimageProcessor.o TestPGMimage.o -o pgm.exe -std=c++20

clean:
	rm *.o
	rm extractor
	rm *.exe