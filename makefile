#OBJNAME=libgentle.a
OBJNAME=filter

include ./makefile.pub

$(OBJNAME):$(objects)
	$(CC) -o $(OBJNAME) $(objects) $(LIB_PATHS) $(LDFLAGS) -rdynamic
