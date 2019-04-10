AR = ar
ARFLAGS = rcs

OBJECTS = ../src
OBJS = deepest.o deepest.pb.o exception.o interface.o machine.o matrix.o model.o projection.o 

.PHONY: clean
vpath %.o $(OBJECTS)

all: libmodel.a libmodel.so

libmodel.a:	$(OBJS)
	@echo "Generating $@"
	$(AR) $(ARFLAGS) $@ $^

libmodel.so: $(OBJS)
	@echo "Generating $@"
	gcc -shared -Wl,-rpath=/$(PROTOBUF_LIBDIR),-soname,libmodel.so -o $@ $^ $(PROTOBUF_LIB)

clean:
	@rm -f libmodel.a libmodel.so
