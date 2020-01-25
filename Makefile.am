# Copyright (C) 2016--2020 jeremy theler
# This file is part of libreblackjack.
# This file is free software: you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.

# SUBDIRS = doc
AUTOMAKE_OPTIONS = subdir-objects
dist_doc_DATA = README
#doc/libreblackjack.texi

TESTS = check-internal.sh check-stand.sh
EXTRA_DIST = config.rpath m4/ChangeLog  libreblackjack.ini players $(TESTS)

# ACLOCAL_AMFLAGS = $(ACLOCAL_FLAGS)
bin_PROGRAMS = libreblackjack
libreblackjack_INCLUDES = $(all_includes)
libreblackjack_LDADD = $(all_libraries) 

libreblackjack_SOURCES = \
 src/libreblackjack.h \
 src/version-vcs.h \
 src/utlist.h \
 src/main.c \
 src/cards.c \
 src/dealer.c \
 src/stdinout.c \
 src/bjinit.c \
 src/commands.c \
 src/version.c \
 src/fifo.c \
 src/error.c \
 src/report.c \
 src/player.c \
 src/internal.c \
 src/shmem.c \
 src/mqueue.c

SUBDIRS = po

ACLOCAL_AMFLAGS = -I m4
