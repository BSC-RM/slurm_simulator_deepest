MPICC = mpicc
DEBUG = -g -Wall

BINS = testMarker

.PHONY: clean

all: $(BINS)

%.o: %.c
	@echo "Generating $@"
	@$(MPICC) -c $<

#------------------------------------------------------------------------------------------------------

testMarker:	testMarker.o
	@echo "Generating $@"
	@$(MPICC) $(DEBUG) $^ -o $@ -lm

#------------------------------------------------------------------------------------------------------

clean:
	@rm -f *.o $(BINS)
