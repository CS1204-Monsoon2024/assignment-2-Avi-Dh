default:
	g++ main.cpp HashTable.cpp -o myProgram

test:
	g++ -o hash Hash.cpp

mainIm:
	g++ -o mainIm main.cpp

clean:
	rm *.out
