PROJ := wg

SOURCES := Weighted_graph.h
SOURCES += Exception.h
#SOURCES += Tester.h
#SOURCES += ece250.h
#SOURCES += Weighted_graph_tester.h
#SOURCES += Weighted_graph_driver.cpp
#SOURCES += Test.cpp
SOURCES += speed.cpp
#SOURCES += speed2.cpp

CFLAGS := -DDEBUG_PRINT
CFLAGS += -g
CFLAGS += -std=c++11
CFLAGS += $(patsubst %,-I%,$(VPATH))
CFLAGS += -O2

$(PROJ):
	g++ $(CFLAGS) $(SOURCES) -o$(PROJ)

# for some reason rm -f $(PROJ) so make it the same as PROJ for now
clean:
	rm -f wg
