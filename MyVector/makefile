TEST_2D =  MyVector.o test_2d.o
TEST_3D =  MyVector.o test_3d.o
BINS = test_3d test_2d

CC = gcc
CXX = g++


LIBS = -lm
ifeq ($(DEF), DEBUG)
     CFLAGS = -g -Wall -Wextra
else
     ifeq ($(DEF), PROF)
		      CFLAGS = -O3 -pg
		 else
		      CFLAGS = -O3
		 endif
endif

all: $(BINS)

test_2d: $(TEST_2D)
	$(CXX) $(TEST_2D) -o $@ $(LIBS) $(CFLAGS)

test_3d: $(TEST_3D)
	$(CXX) $(TEST_3D) -o $@ $(LIBS) $(CFLAGS)


#####################################################

clean:
	rm -f *.o

cleanall: clean
	rm -f $(BINS)

#####################################################
.SUFFIXES: .f90 .f .o .mod .F .c .cpp

.c.o:
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CXX) $(CFLAGS) -c $<
