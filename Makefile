EXTENSION = pg_jewelry_tools
DATA = pg_jewelry_tools--0.0.1.sql

MODULE_big = pg_jewelry_tools
OBJS = src/jw_func.o

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)