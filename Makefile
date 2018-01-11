MODULE_big=coordconv
EXTENSION=coordconv
EXTVERSION:=$(shell grep default_version $(EXTENSION).control | \
		 sed -e "s/default_version[[:space:]]*=[[:space:]]*'\([^']*\)'/\1/")
OBJS=pgcoord.o wcscon.o
#DATA_built=coordconv.sql
#DOCS=README.q3c
DATA = $(wildcard scripts/*sql)

OPT=-O3 -mtune=native -march=native
OPT_LOW=-O2
#DEBUG=-g3 -ggdb -DQ3C_DEBUG
PG_CPPFLAGS = $(DEBUG) $(OPT) -D_GNU_SOURCE
SHLIB_LINK += $(filter -lm, $(LIBS))

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
