# SUBDIRS = doc
AUTOMAKE_OPTIONS = subdir-objects
dist_doc_DATA = README
#doc/libreblackjack.texi

TESTS = 00-always-stand 05-no-bust 08-mimic-the-dealer 22-strategy-from-file
LOG_COMPILER = players/check.sh
EXTRA_DIST = players src/version.sh $(TESTS)

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
 src/shmem.c \
 src/mqueue.c

version.$(OBJEXT): src/version.h
version.h: Makefile
	cd src; ./version.sh; cd ..
