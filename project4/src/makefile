PROJ := qht

SOURCES := Quadratic_hash_table.h
SOURCES += Exception.h
SOURCES += Tester.h
SOURCES += ece250.h
SOURCES += Quadratic_hash_table_driver.cpp
SOURCES += Quadratic_hash_table_tester.h

CFLAGS := -DDEBUG_PRINT
CFLAGS += -g
CFLAGS += -std=c++11
CFLAGS += $(patsubst %,-I%,$(VPATH))

$(PROJ):
	g++ $(CFLAGS) $(SOURCES) -o$(PROJ)

# for some reason rm -f $(PROJ) so make it the same as PROJ for now
clean:
	rm -f qht
