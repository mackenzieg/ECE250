PROJ := rd 

SOURCES := Resizable_deque.h
SOURCES += Exception.h
SOURCES += Resizable_deque_tester.h
SOURCES += Tester.h
SOURCES += ece250.h
SOURCES += main.cpp
#SOURCES += Resizable_deque_driver.cpp

CFLAGS := -DDEBUG_PRINT
CFLAGS += -g
CFLAGS += -std=c++11
CFLAGS += $(patsubst %,-I%,$(VPATH))

$(PROJ):
	g++ $(CFLAGS) $(SOURCES) -o$(PROJ)

# for some reason rm -f $(PROJ) so make it the same as PROJ for now
clean:
	rm -f rd
