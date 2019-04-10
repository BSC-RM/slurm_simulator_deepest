NAME = model
VERSION = 1.0

LIB_SOURCE = lib
SRC_SOURCE = src
BIN_SOURCE = tests
MODEL_SOURCE = model
INCLUDE_SOURCE = include

#LIB_TARGET = /lrz/sys/libraries/$(NAME)/$(VERSION)
#INCLUDE_TARGET = /lrz/sys/libraries/$(NAME)/$(VERSION)
#BIN_TARGET = /usr/local/bin
BACKUP_TARGET = backup

MAKE = make
MV = mv
CP = cp
RM = rm
TAR = tar -cvzf
DATE = `date +%Y%m%0d`

all: source model tests

source:
	@echo "Cleaning old version"
	@$(MAKE) -C $(SRC_SOURCE)/ clean
	@$(MAKE) -C $(LIB_SOURCE)/ clean
	@echo "Compiling source..."
	@$(MAKE) -C $(SRC_SOURCE)/
	@$(MAKE) -C $(LIB_SOURCE)/

model:
	@echo "Cleaning old version"
	@$(MAKE) -C $(MODEL_SOURCE)/ clean
	@echo "Compiling model..."
	@$(MAKE) -C $(MODEL_SOURCE)/
	
tests:
	@echo "Cleaning old version"
	@$(MAKE) -C $(BIN_SOURCE)/ clean
	@echo "Compiling tests..."
	@$(MAKE) -C $(BIN_SOURCE)/

.PHONY: clean
clean:
	@echo "Cleaning old version"
	@$(MAKE) -C $(SRC_SOURCE)/ clean
	@$(MAKE) -C $(LIB_SOURCE) clean
	@$(RM) $(LIB_TARGET)/lib/$(LIBNAME)
	@$(RM) $(INCLUDE_TARGET)/include/*.h
	@$(RM) $(BIN_TARGET)/PAPIServer

.PHONY: install
install:
	@echo "Copying library to $(LIB_TARGET)/lib directory"
	@$(MV) $(LIB_SOURCE)/$(LIBNAME) $(LIB_TARGET)/lib/$(LIBNAME)
	@echo "Copying headers to $(INCLUDE_TARGET)/include directory"
	@$(CP) $(INCLUDE_SOURCE)/*.h $(INCLUDE_TARGET)/include/
	@echo "Copying server to $(BIN_TARGET) directory"
	@$(CP) $(BIN_SOURCE)/PAPIServer $(BIN_TARGET)

.PHONY: archive
archive:	
	@echo Performing a backup to the $(BACKUP_TARGET) directory
	@$(TAR) $(BACKUP_TARGET)/$(DATE).tgz  $(INCLUDE_SOURCE)/* $(SRC_SOURCE)/* $(LIB_SOURCE)/*.a $(LIB_SOURCE)/*.so
