CXXFLAGS := $(CXXFLAGS) -g -I ../include
ALL_BINS := $(patsubst %.cpp,%.out,$(wildcard *.cpp))

all: $(ALL_BINS)

%.out: %.cpp
	$(CXX) $< $(CXXFLAGS) $(LDFLAGS) -o $@

clean:
	rm -f $(ALL_BINS)

.PHONY: all clean
