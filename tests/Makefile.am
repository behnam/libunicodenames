#  Copyright (C) 2012 Barry Schwartz
# 
#  This file is part of LibUnicodeNames.
#  
#  LibUnicodeNames is free software: you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public License
#  as published by the Free Software Foundation, either version 3 of
#  the License, or (at your option) any later version.
#  
#  LibUnicodeNames is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#  
#  You should have received a copy of the GNU Lesser General Public
#  License along with LibUnicodeNames.  If not, see
#  <http://www.gnu.org/licenses/>.

#--------------------------------------------------------------------------

# The `:;' works around a Bash 3.2 bug when the output is not writable.
$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	:;{ \
		echo '# Signature of the current package.' && \
		echo 'm4_define([AT_PACKAGE_NAME],' && \
		echo '  [$(PACKAGE_NAME)])' && \
		echo 'm4_define([AT_PACKAGE_TARNAME],' && \
		echo '  [$(PACKAGE_TARNAME)])' && \
		echo 'm4_define([AT_PACKAGE_VERSION],' && \
		echo '  [$(PACKAGE_VERSION)])' && \
		echo 'm4_define([AT_PACKAGE_STRING],' && \
		echo '  [$(PACKAGE_STRING)])' && \
		echo 'm4_define([AT_PACKAGE_BUGREPORT],' && \
		echo '  [$(PACKAGE_BUGREPORT)])'; \
		echo 'm4_define([AT_PACKAGE_URL],' && \
		echo '  [$(PACKAGE_URL)])'; \
	} >'$(srcdir)/package.m4'

EXTRA_DIST = testsuite.at $(srcdir)/package.m4 $(TESTSUITE) atlocal.in
TESTSUITE = $(srcdir)/testsuite

check-local: atconfig atlocal $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' $(TESTSUITEFLAGS)

installcheck-local: atconfig atlocal $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(bindir)' $(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || $(SHELL) '$(TESTSUITE)' --clean

AUTOM4TE = $(SHELL) $(srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(srcdir)/testsuite.at $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $@.at
	mv $@.tmp $@

#--------------------------------------------------------------------------

TESTS_ENVIRONMENT = @LOCALCHARSET_TESTS_ENVIRONMENT@

dist_noinst_SCRIPTS = import_unicodenames.py create_delete.py			\
	names_db_locale.py patch_test.py blocks.py blocks_index_error.py

check_PROGRAMS =

check_PROGRAMS += c_create_delete
c_create_delete_SOURCES = c_create_delete.c
c_create_delete_LDADD = $(top_builddir)/libunicodenames.la $(LDADD)

check_PROGRAMS += c_names_db_locale
c_names_db_locale_SOURCES = c_names_db_locale.c
c_names_db_locale_LDADD = $(top_builddir)/libunicodenames.la $(LDADD)

check_PROGRAMS += c_patch_test
c_patch_test_SOURCES = c_patch_test.c
c_patch_test_LDADD = $(top_builddir)/libunicodenames.la $(LDADD)

#--------------------------------------------------------------------------

if CXX_FFI

check_PROGRAMS += cxx_create_delete
cxx_create_delete_SOURCES = cxx_create_delete.cxx
cxx_create_delete_LDADD = $(top_builddir)/libunicodenames++.la			\
	$(top_builddir)/libunicodenames.la $(LDADD)

check_PROGRAMS += cxx_names_db_locale
cxx_names_db_locale_SOURCES = cxx_names_db_locale.cxx
cxx_names_db_locale_LDADD = $(top_builddir)/libunicodenames++.la		\
	$(top_builddir)/libunicodenames.la $(LDADD)

check_PROGRAMS += cxx_patch_test
cxx_patch_test_SOURCES = cxx_patch_test.cxx
cxx_patch_test_LDADD = $(top_builddir)/libunicodenames++.la \
	$(top_builddir)/libunicodenames.la $(LDADD)

endif CXX_FFI

#--------------------------------------------------------------------------

AM_CPPFLAGS = -I$(top_builddir)/lib -I$(top_srcdir)/lib	\
	-I$(top_srcdir)
AM_CFLAGS = $(WARNING_CFLAGS)
AM_CXXFLAGS = $(WARNING_CXXFLAGS)
AM_LDFLAGS = $(LTLIBINTL)
LDADD = $(top_builddir)/lib/libgnu.la

check-local: override TESTSUITEFLAGS += LIBUNICODENAMES_INSTALLED=no

installcheck-local: override TESTSUITEFLAGS += LIBUNICODENAMES_INSTALLED=yes

DISTCLEANFILES = atconfig

#--------------------------------------------------------------------------

include $(top_srcdir)/indent.mk

indent:
	$(call do_indent, $(c_create_delete_SOURCES))
	$(call do_indent, $(cxx_create_delete_SOURCES))
	$(call do_indent, $(c_names_db_locale_SOURCES))
	$(call do_indent, $(cxx_names_db_locale_SOURCES))
	$(call do_indent, $(c_patch_test_SOURCES))
	$(call do_indent, $(cxx_patch_test_SOURCES))

#--------------------------------------------------------------------------
