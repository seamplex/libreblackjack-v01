# Copyright (C) 2019 jeremy theler
# This file is part of libreblackjack.
# This file is free software: you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.

# SUBDIRS = doc
AUTOMAKE_OPTIONS = subdir-objects
dist_doc_DATA = README
#doc/libreblackjack.texi

TESTS = 00-internal 02-always-stand 05-no-bust 08-mimic-the-dealer
LOG_COMPILER = players/check.sh
EXTRA_DIST = libreblackjack.ini  src/version.sh src/version-vcs.h players $(TESTS)

# ACLOCAL_AMFLAGS = $(ACLOCAL_FLAGS)
bin_PROGRAMS = libreblackjack
libreblackjack_INCLUDES = $(all_includes)
libreblackjack_LDADD = $(all_libraries) 

libreblackjack_SOURCES = \
 src/libreblackjack.h \
 src/utlist.h \
 src/main.c \
 src/cards.c \
 src/dealer.c \
 src/stdinout.c \
 src/ini.c \
 src/ini.h \
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

version.$(OBJEXT): src/version.h
version.h: Makefile
	cd src; ./version.sh; cd ..
