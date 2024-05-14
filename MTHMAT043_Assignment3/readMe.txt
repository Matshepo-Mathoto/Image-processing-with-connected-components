Read me
1.ConnectedComponent.h
2. ConnectedComponent.cpp
- is the header file and contains all the methods that ConnectedComponent.cpp, pgmImageProcessor.cpp and Driver.cpp file will require
2. ConnectedComponent.cpp
- contains the implementation of all the methods in the ConnectedComponent header
3.pgmImageProcessor.h
- is the header file and contains all the methods that both the pgmImageProcessor.cpp and Driver.cpp file will require
4. pgmImageProcessor.cpp
- contains the implementation of all the methods in the pgmImageProcessor header
5.Driver.cpp
- Contain the main method that read the file and call the methods in the pgmImageProcessor to perform a required action.
 The main method can only make correct output.
6.TestpgmImageProcessor.cpp
- contains test cases for the 6 big constructor and methods
7.TestConnectedComponent.cpp
- contains test cases for the 6 big constructor

main program :
use make to compile
To run the program: ProgramName -s min max -t threshold -p -w outputImageName InputImage
e.g ./extractor -s 3 70000 -t 29 -p -w matshepo Birds_Colours

TestConnectedComponent:
use make run 
./comp.exe to execute

TestpgmImageProcessor:
use make run1
./pgm.exe to execute

