MODULE_big=coordconv
OBJS=pgcoord.o wcscon.o
DATA_built=coordconv.sql
#DOCS=README.q3c

OPT=-O3 -mtune=native -march=native
OPT_LOW=-O2
#DEBUG=-g3 -ggdb -DQ3C_DEBUG
PG_CPPFLAGS = $(DEBUG) $(OPT) -D_GNU_SOURCE
SHLIB_LINK += $(filter -lm, $(LIBS))

ifdef NO_PGXS
subdir = contrib/coord
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
else
PGXS := $(shell pg_config --pgxs)
ifndef PGXS
$(error You should have `pg_config` program in your PATH or compile Q3C with\
'make NO_PGXS=1' \
after putting it in the contrib subdirectory of Postgres sources)
endif
include $(PGXS)

endif

