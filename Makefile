#------------------------------------------------------------------------------
#	File: Makefile
#	Name: Andrew Craig
#	CruzID: acraig1
#	Assignment: pa5
#
#
#  make                     makes FindComponents
#  make GraphTest     		makes GraphTest
#  make ListTest            makes ListTest
#  make clean               removes all binaries
#  make memcheck            runs Graph Client under valgrind
#------------------------------------------------------------------------------

CLIENT         = FindComponents
ADT1           = Graph
ADT2           = List
ADT1_TEST      = GraphTest
ADT2_TEST      = ListTest
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
ADT1_TEST_SOURCE = $(ADT1_TEST).c
ADT1_TEST_OBJECT = $(ADT1_TEST).o
ADT2_TEST_SOURCE = $(ADT2_TEST).c
ADT2_TEST_OBJECT = $(ADT2_TEST).o

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_TEST) : $(ADT1_TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(ADT1_TEST) $(ADT1_TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(ADT1_TEST_OBJECT) : $(ADT1_TEST_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(ADT1_TEST_SOURCE)

$(ADT2_TEST) : $(ADT2_TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(ADT2_TEST) $(ADT2_TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(ADT2_TEST_OBJECT) : $(ADT2_TEST_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_TEST_SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) $(ADT1_TEST_OBJECT) $(ADT2_TEST_OBJECT)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)
