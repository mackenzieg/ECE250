PROJ := ll

SOURCES := Double_sentinel_list.h
SOURCES += Exception.h
SOURCES += Double_sentinel_list_tester.h
SOURCES += Tester.h
SOURCES += ece250.h
#SOURCES += Double_sentinel_list_driver.cpp
SOURCES += tb.cpp

CFLAGS := -DDEBUG_PRINT
CFLAGS += -g
CFLAGS += -std=c++11
CFLAGS += $(patsubst %,-I%,$(VPATH))

$(PROJ):
	g++ $(CFLAGS) $(SOURCES) -o$(PROJ)

# for some reason rm -f $(PROJ) so make it the same as PROJ for now
clean:
	rm -f ll
