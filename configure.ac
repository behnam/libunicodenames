#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

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

AC_PREREQ([2.68])
AC_INIT([libunicodenames],[1.0.0_beta6],[https://github.com/sortsmill/libunicodenames/issues])
AC_CONFIG_SRCDIR([make-names-db.awk])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_TESTDIR([tests])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.12.2 -Wall -Wno-portability])
AM_MAINTAINER_MODE([enable])
AC_USE_SYSTEM_EXTENSIONS
m4_ifdef([AM_PROG_AR],[AM_PROG_AR])
LT_INIT
AM_GNU_GETTEXT_VERSION([0.18.1])

# I am going to try enabling silent-rules by default, so builders are
# more likely to see warnings. Use --disable-silent-rules or "make
# V=1" if you need to see the rules.
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

VERSION_MAJOR=`AS_ECHO(["${PACKAGE_VERSION}"]) | sed -e 's/^\([[0-9]][[0-9]]*\).*/\1/'`
VERSION_MINOR=`AS_ECHO(["${PACKAGE_VERSION}"]) | sed -e 's/^[[0-9]][[0-9]]*\.\([[0-9]][[0-9]]*\).*/\1/'`
VERSION_PATCH=`AS_ECHO(["${PACKAGE_VERSION}"]) | sed -e 's/^[[0-9]][[0-9]]*\.[[0-9]][[0-9]]*\.\([[0-9]][[0-9]]*\).*/\1/'`
VERSION_EXTRA=`AS_ECHO(["${PACKAGE_VERSION}"]) | sed -e 's/^[[0-9]][[0-9]]*\.[[0-9]][[0-9]]*\.[[0-9]][[0-9]]*\(.*\)/\1/' \
                                                     -e 's/^_//'`
VERSION_EXTRA_SHORT=`AS_ECHO(["${VERSION_EXTRA}"]) | sed -e 's/alpha/a/' -e 's/beta/b/'`
AC_SUBST([VERSION_MAJOR])
AC_SUBST([VERSION_MINOR])
AC_SUBST([VERSION_PATCH])
AC_SUBST([VERSION_EXTRA])
AC_SUBST([VERSION_EXTRA_SHORT])


#--------------------------------------------------------------------------
#
# Checks for programs.

AC_PROG_CC
AC_PROG_CC_C99
gl_EARLY
gl_INIT
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_CXX_C_O
AC_PROG_CPP
AC_PROG_AWK
AC_PROG_YACC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_PROG_SED
AM_PATH_PYTHON([],[],[:])
AC_PATH_PROGS([GAWK],[gawk],[gawk])
AC_PATH_PROGS([INDENT],[indent],[indent])
AC_PATH_PROGS([WGET],[wget],[wget])

AC_ARG_ENABLE([c++],[AS_HELP_STRING([--enable-c++],[build C++ bindings])])
AC_SUBST([enable_c__])
AM_CONDITIONAL([CXX_FFI],[test x"${enable_c__}" = xyes])

AC_ARG_ENABLE([python],
   [AS_HELP_STRING([--enable-python],
                   [build Python bindings (requires --enable-c++ and SWIG >= 2.0.4)])],
   [
      AM_PATH_PYTHON
      AX_PKG_SWIG([2.0.4],[],[AC_MSG_ERROR([SWIG is required to build the Python bindings.])])
      AX_SWIG_PYTHON
   ])
AC_SUBST([enable_python])
AM_CONDITIONAL([PYTHON_FFI],[test x"${enable_python}" = xyes])

if test x"${enable_python}" = xyes -a x"${enable_c__}" != xyes; then
   AC_MSG_ERROR([--enable-python requires --enable-c++])
fi


#--------------------------------------------------------------------------
#
# Checks for libraries.


#--------------------------------------------------------------------------
#
# Checks for header files.

AC_CHECK_HEADERS([argz.h fcntl.h float.h inttypes.h langinfo.h libintl.h limits.h locale.h malloc.h stddef.h stdint.h stdio_ext.h stdlib.h string.h sys/param.h unistd.h wchar.h])
AC_HEADER_STDBOOL
AC_FUNC_ALLOCA


#--------------------------------------------------------------------------
#
# Checks for typedefs, structures, and compiler characteristics.

AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

AC_LANG_PUSH([C])
AC_SUBST([WARNING_CFLAGS],[])
AX_CHECK_COMPILE_FLAG([-Wall],[WARNING_CFLAGS+=" -Wall"])
AX_CHECK_COMPILE_FLAG([-Wextra],[WARNING_CFLAGS+=" -Wextra"])
AX_CHECK_COMPILE_FLAG([-Wcast-align],[WARNING_CFLAGS+=" -Wcast-align"])
AX_CHECK_COMPILE_FLAG([-Wbad-function-cast],[WARNING_CFLAGS+=" -Wbad-function-cast"])
AX_CHECK_COMPILE_FLAG([-Wc++-compat],[WARNING_CFLAGS+=" -Wc++-compat"])
AX_CHECK_COMPILE_FLAG([-Wno-unused-result],[WARNING_CFLAGS+=" -Wno-unused-result"])
AC_LANG_POP

if test x"${enable_c__}" = xyes; then
   AC_LANG_PUSH([C++])

   AC_SUBST([WARNING_CXXFLAGS],[])
   AX_CHECK_COMPILE_FLAG([-Wall],[WARNING_CXXFLAGS+=" -Wall"])
   AX_CHECK_COMPILE_FLAG([-Wextra],[WARNING_CXXFLAGS+=" -Wextra"])
   AX_CHECK_COMPILE_FLAG([-Wcast-align],[WARNING_CXXFLAGS+=" -Wcast-align"])
   AX_CHECK_COMPILE_FLAG([-Wno-unused-result],[WARNING_CXXFLAGS+=" -Wno-unused-result"])

   AC_SUBST([SWIG_PYTHON_WARNING_CXXFLAGS],[])
   AX_CHECK_COMPILE_FLAG([-Wno-unused-but-set-variable],
                         [SWIG_PYTHON_WARNING_CXXFLAGS+=" -Wno-unused-but-set-variable"])

   AC_LANG_POP
fi

VISIBLE=''
test x"${HAVE_VISIBILITY}" = x1 && VISIBLE='__attribute__((__visibility__("default")))'
AC_DEFINE_UNQUOTED([VISIBLE],[${VISIBLE}],
        [Define to the attribute for a visible symbol in a shared library.])


#--------------------------------------------------------------------------
#
# Checks for library functions.

AC_FUNC_MALLOC
AM_GNU_GETTEXT([external])
AC_FUNC_MALLOC
AC_FUNC_MBRTOWC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([__argz_count __argz_next __argz_stringify floor getcwd localeconv mblen mbrlen memchr mempcpy memset munmap nl_langinfo setlocale stpcpy strcasecmp strchr strcspn strdup strstr strtoul])

#--------------------------------------------------------------------------

AC_SUBST([LT_OBJDIR],["${lt_cv_objdir}"])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([libunicodenames.pc libunicodenames++.pc])
AC_CONFIG_FILES([unicodenames.i])
AC_CONFIG_FILES([lib/Makefile])
AC_CONFIG_FILES([po/Makefile.in])
AC_CONFIG_FILES([tests/Makefile tests/atlocal])

AC_CONFIG_COMMANDS([.indent.pro],
   [
      if test "${ac_srcdir}" -ef "${ac_builddir}"; then
         :
      else
         for dir in . tests; do
             rm -f "${ac_builddir}/${dir}/.indent.pro"
             (cd "${ac_builddir}/${dir}" && ${LN_S} "${ac_srcdir}"/.indent.pro .indent.pro)
         done
      fi
   ])

AC_OUTPUT

#--------------------------------------------------------------------------
