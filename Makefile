TARGET?=program

BUILDDIR := obj

INCLUDE_DIRS?=	./ \
				./unity/extras/fixture/src/ \
				./unity/src/

INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)


CFLAGS?=-g -Wall $(INC_PARAMS)

SOURCE_FILES = $(wildcard *.c)
SOURCE_FILES+=	./unity/src/unity.c \
				./unity/extras/fixture/src/unity_fixture.c


obj = $(SOURCE_FILES:.c=.o)
dep = $(obj:.o=.d)  


OBJS := $(patsubst %.c, ./$(BUILDDIR)/%.o, $(notdir $(obj)))

LDFLAGS = 


all: directories $(BUILDDIR)/$(TARGET)


directories:
	@mkdir -p $(BUILDDIR)	


$(BUILDDIR)/$(TARGET): $(BUILDDIR)/$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)	


-include $(dep)   

unity.o : 
	make -C unity



%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@


%.d: %.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$(BUILDDIR)/$@

.PHONY: clean
clean:
	rm -f *.d *.o myprog

.PHONY: cleandep
cleandep:
	rm -f $(dep)