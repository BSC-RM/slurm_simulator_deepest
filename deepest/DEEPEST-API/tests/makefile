CC = gcc

DEBUG = -g -Wall

CFLAGS = $(DEBUG) -std=c++11 -fPIC  
INCLUDE = ../include
LINCLUDE = -I$(INCLUDE)

LIBS = -lstdc++ -pthread -L../lib -lmodel -L/usr/local/lib -lprotobuf 

BINS = test_conf test_conf_C 

.PHONY: clean
vpath %.h $(INCLUDE)

all: $(BINS)

#------------------------------------------------------------------------------------------------------

%.o: %.cpp
	@echo "Generating $@"
	@$(CC) $(CFLAGS) $(LINCLUDE) $(DAEMON) -c $<

%.o: %.c
	@echo "Generating $@"
	@$(CC) $(CFLAGS) $(LINCLUDE) $(DAEMON) -c $<

#------------------------------------------------------------------------------------------------------

test_conf: test_conf.o
	@echo "Generating test binary $@"
	@$(CC) $^ -o $@ $(LIBS)

test_conf_C: test_conf_C.o
	@echo "Generating test binary $@"
	@$(CC) $^ -o $@ $(LIBS)
	
write_conf: write_conf.o
	@echo "Generating test binary $@"
	@$(CC) $^ -o $@ $(LIBS)

test_matrix: test_matrix.o
	@echo "Generating test binary $@"
	@$(CC) $^ -o $@ $(LIBS)

#------------------------------------------------------------------------------------------------------

clean:
	@rm -f *.o
