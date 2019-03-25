CC = gcc
CFLAGS  = -g -Wall

default: boggle

boggle: main.o GenBoard.o WordList.o WordFind.o PlayerVersusComputerAcc.o PlayerVersusPlayerAcc.o PlayerAcc.o ComputerVersusComputerAcc.o
	$(CC) $(CFLAGS) -o boggle  main.o GenBoard.o WordList.o WordFind.o PlayerVersusComputerAcc.o PlayerVersusPlayerAcc.o PlayerAcc.o ComputerVersusComputerAcc.o

main.o:  main.c SinglePlayer.c Multiplayer.c
	$(CC) $(CFLAGS) -c main.c

GenBoard.o: GenBoard.c GenBoard.h
	$(CC) $(CFLAGS) -c GenBoard.c

WordList.o: WordList.c WordList.h
	$(CC) $(CFLAGS) -c WordList.c

WordFind.o: WordFind.c WordFind.h
	$(CC) $(CFLAGS) -c WordFind.c

PlayerVersusComputerAcc.o: PlayerVersusComputerAcc.c PlayerVersusComputerAcc.h WordFind.h
	$(CC) $(CFLAGS) -c PlayerVersusComputerAcc.c

PlayerVersusPlayerAcc.o: PlayerVersusPlayerAcc.c PlayerVersusPlayerAcc.h WordFind.h
	$(CC) $(CFLAGS) -c PlayerVersusPlayerAcc.c

PlayerAcc.o: PlayerAcc.c PlayerAcc.h WordFind.h
	$(CC) $(CFLAGS) -c PlayerAcc.c

ComputerVersusComputerAcc.o: ComputerVersusComputerAcc.c ComputerVersusComputerAcc.h WordFind.h
	$(CC) $(CFLAGS) -c ComputerVersusComputerAcc.c



clean:
	$(RM) boggle *.o *~
