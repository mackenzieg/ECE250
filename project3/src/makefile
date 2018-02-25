PROJ := st

SOURCES := Search_tree.h
SOURCES += Exception.h
SOURCES += ece250.h
SOURCES += test.cpp
#SOURCES += Resizable_deque_driver.cpp

CFLAGS := -DDEBUG_PRINT
CFLAGS += -g
CFLAGS += -std=c++11
CFLAGS += $(patsubst %,-I%,$(VPATH))

$(PROJ):
	g++ $(CFLAGS) $(SOURCES) -o$(PROJ)

# for some reason rm -f $(PROJ) so make it the same as PROJ for now
clean:
	rm -f st
