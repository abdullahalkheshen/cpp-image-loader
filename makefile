CC=g++
SRC=./src/
INC=./include/

make: 
	$(CC) $(SRC)*.cpp -I$(INC) -o $(SRC)main

debug:
	$(CC) -g $(SRC)*.cpp -I$(INC) -o $(SRC)main

clean:
	rm $(SRC)main.exe