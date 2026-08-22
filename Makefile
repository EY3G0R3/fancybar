# fancybar - a tiny progress-bar formatter for status lines
.POSIX:

# ?= so an exported PREFIX is honoured; a command-line PREFIX=... overrides
# either form.
PREFIX ?= $(HOME)/.local

# = and not ?=: POSIX make predefines CC and CFLAGS (c99 and -O1 here), so ?=
# would yield to those built-ins and silently drop every flag below. A
# command-line CC=/CFLAGS= still overrides this.
CC     = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Os

all: fancybar

fancybar: fancybar.c
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) fancybar.c

clean:
	rm -f fancybar

install: all
	mkdir -p "$(DESTDIR)$(PREFIX)/bin"
	cp -f fancybar "$(DESTDIR)$(PREFIX)/bin"
	chmod 755 "$(DESTDIR)$(PREFIX)/bin/fancybar"

uninstall:
	rm -f "$(DESTDIR)$(PREFIX)/bin/fancybar"

.PHONY: all clean install uninstall
