CC = gcc
MPICC = mpicc

INCLUDE = ../include
LINCLUDE = -I$(INCLUDE) $(PROTOBUF_INC)

LIBS = -lstdc++ -lpthread $(PROTOBUF_LIB)

# DEBUG INFORMATION
#DEBUG = -DDEBUGMODE
DEBUG = -g -Wall

#DAEMON = -DACCESSDAEMON

CFLAGS = $(DEBUG) -std=c++11 -fPIC  

OBJS = deepest.o deepest.pb.o exception.o interface.o machine.o matrix.o model.o projection.o

.PHONY: clean
vpath %.h $(INCLUDE)

all: $(OBJS)

projection.o:	projection.cpp projection.h
	@echo "Generating $@"
	@$(CC) $(CFLAGS) $(LINCLUDE) $(PROTOBUF_INC) -c $<
	
%.o: %.cpp
	@echo "Generating $@"
	@$(CC) $(CFLAGS) $(LINCLUDE) $(DAEMON) -c $<

%.o: %.cc
	@echo "Generating $@"
	@$(CC) $(CFLAGS) $(LINCLUDE) $(PROTOBUF_INC) -c $<

%.o: %.c
	@echo "Generating $@"
	@$(CC) $(CFLAGS) $(LINCLUDE) $(DAEMON) -c $<

#------------------------------------------------------------------------------------------------------

deepest.o: deepest.cpp deepest.h
deepest.pb.o: deepest.pb.cc deepest.pb.h
exception.o: exception.cpp exception.h defines.h
interface.o: interface.cpp interface.h
machine.o: machine.cpp machine.h defines.h
matrix.o: matrix.cpp matrix.h
model.o: machine.cpp model.cpp model.h defines.h matrix.h
projection.o: projection.cpp deepest.pb.o machine.h matrix.h model.h projection.h 

#------------------------------------------------------------------------------------------------------

clean:
	@rm -f *.o
