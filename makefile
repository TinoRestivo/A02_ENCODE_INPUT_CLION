#
# this makefile will compile and and all source
# found in the "encodeInput" directory. 
# 
# =======================================================
#                  encodeInput
# =======================================================
# FINAL BINARY Target
./bin/encodeInput : ./obj/encodeInput.o ./obj/inputFile.o ./obj/outputFile.o ./obj/parseCommandLine.o ./obj/asmFile.o ./obj/srec.o
	cc -g ./obj/encodeInput.o ./obj/inputFile.o ./obj/outputFile.o ./obj/parseCommandLine.o ./obj/asmFile.o ./obj/srec.o -o ./bin/encodeInput
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/encodeInput.o : ./src/encodeInput.c ./inc/inputFile.h ./inc/outputFile.h ./inc/parseCommandLine.h inc/asmFile.h ./inc/srec.h
	cc -c -g ./src/encodeInput.c -o ./obj/encodeInput.o

./obj/inputFile.o : ./src/inputFile.c ./inc/inputFile.h
	cc -c -g ./src/inputFile.c -o ./obj/inputFile.o

./obj/outputFile.o : ./src/outputFile.c ./inc/outputFile.h
	cc -c -g ./src/outputFile.c -o ./obj/outputFile.o

./obj/parseCommandLine.o : ./src/parseCommandLine.c ./inc/parseCommandLine.h
	cc -c -g ./src/parseCommandLine.c -o ./obj/parseCommandLine.o

./obj/asmFile.o : src/asmFile.c inc/asmFile.h
	cc -c -g ./src/asmFile.c -o ./obj/asmFile.o

./obj/srec.o : ./src/srec.c ./inc/srec.h
	cc -c -g ./src/srec.c -o ./obj/srec.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/encodeInput

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


