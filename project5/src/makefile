PROJ := wg

SOURCES := Weighted_graph.h
SOURCES += Exception.h
SOURCES += Tester.h
SOURCES += ece250.h
#SOURCES += Test.cpp
SOURCES += Weighted_graph_tester.h
SOURCES += Weighted_graph_driver.cpp

CFLAGS := -DDEBUG_PRINT
CFLAGS += -g
CFLAGS += -std=c++11
CFLAGS += $(patsubst %,-I%,$(VPATH))

$(PROJ):
	g++ $(CFLAGS) $(SOURCES) -o$(PROJ)

# for some reason rm -f $(PROJ) so make it the same as PROJ for now
clean:
	rm -f wg
