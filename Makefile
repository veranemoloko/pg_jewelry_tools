MODULE_big = pg_jewelry_tools
OBJS = src/pg_jewelry_tools.o

EXTENSION = pg_jewelry_tools
DATA = sql/pg_jewelry_tools--0.0.1.sql

REGRESS = test_jewelry
REGRESS_OPTS = --inputdir=test --outputdir=test_results --user=postgres

PG_CFLAGS += -std=c11
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

.PHONY: rebuild
rebuild:
	make clean && make install 

.PHONY: clean
clean:
	rm -f $(OBJS) $(MODULE_big).so
	rm -rf test_results
	rm -rf src/*.o
	rm -rf src/*.bc
	rm -fr *.so


