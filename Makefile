CPP=g++
CPPFLAGS=-g -Wall -Wextra

CHOC_AN_MAIN=src/main.cpp
TESTS=TestDate.cpp

TEST_MAINS=$(addprefix tests/,$(TESTS))
TEST_BINS=$(subst .cpp,,$(TEST_MAINS))
MAINS=$(CHOC_AN_MAIN) $(TEST_MAINS)
SOURCES=$(filter-out $(MAINS),$(wildcard src/*.cpp))
HEADERS=$(wildcard src/*.h)

choc-an: $(SOURCES) $(HEADERS) $(CHOC_AN_MAIN)
	$(CPP) $(CPPFLAGS) $(SOURCES) $(CHOC_AN_MAIN) -o $@

test: $(SOURCES) $(HEADERS) $(TEST_BINS)
	@for main_file in $(TEST_MAINS); do \
		exec_file=$${main_file%%.cpp} ;\
		echo == $${main_file} == ;\
		$${exec_file} ;\
	done

$(TEST_BINS): $(SOURCES) $(HEADERS) $(TEST_MAINS)
	$(CPP) $(CPPFLAGS) $(SOURCES) $@.cpp -o $@

.PHONY: clean test-all
clean:
	rm -fv choc-an
	rm -fv $(subst .cpp,,$(TEST_MAINS))

