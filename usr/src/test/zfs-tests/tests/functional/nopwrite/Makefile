#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2012 by Delphix. All rights reserved.
#

include $(SRC)/Makefile.master

ROOTOPTPKG = $(ROOT)/opt/zfs-tests
TESTDIR = $(ROOTOPTPKG)/tests/functional/nopwrite

PROGS = cleanup \
	nopwrite.shlib \
	nopwrite_copies \
	nopwrite_mtime \
	nopwrite_negative \
	nopwrite_promoted_clone \
	nopwrite_recsize \
	nopwrite_sync \
	nopwrite_varying_compression \
	nopwrite_volume \
	setup

CMDS = $(PROGS:%=$(TESTDIR)/%)
$(CMDS) := FILEMODE = 0555

all lint clean clobber:

install: $(CMDS)

$(CMDS): $(TESTDIR)

$(TESTDIR):
	$(INS.dir)

$(TESTDIR)/%.shlib: %.shlib
	$(INS.file)

$(TESTDIR)/%: %.ksh
	$(INS.rename)
