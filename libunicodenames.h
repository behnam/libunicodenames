/*
// Copyright (C) 2012 Barry Schwartz
//
// This file is part of LibUnicodeNames.
// 
// LibUnicodeNames is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
// 
// LibUnicodeNames is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with LibUnicodeNames.  If not, see
// <http://www.gnu.org/licenses/>.
*/

#ifndef _LIBUNICODENAMES_H
#define _LIBUNICODENAMES_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct uninm_blocks_record
  {
    unsigned int start_point;
    unsigned int end_point;
  } uninm_blocks_record;

  /* A names db handle. */
  typedef struct uninm_names___db *uninm_names_db;

  /* A blocks db handle. */
  typedef struct uninm_blocks___db *uninm_blocks_db;

  /* Get the path of the names db for the current locale. The string
     should be freed by the caller. If locale_base is non-NULL, then
     use it as the base directory for MO files; otherwise use the
     compiled-in locale directory. */
  char *uninm_find_names_db (const char *locale_base);

  /* Get the path of the blocks db for the current locale. The string
     should be freed by the caller. If locale_base is non-NULL, then
     use it as the base directory for MO files; otherwise use the
     compiled-in locale directory. */
  char *uninm_find_blocks_db (const char *locale_base);

  /* Open a names db. */
  uninm_names_db uninm_names_db_open (const char *filename);

  /* Open a blocks db. */
  uninm_blocks_db uninm_blocks_db_open (const char *filename);

  /* Close a names db. */
  void uninm_names_db_close (uninm_names_db handle);

  /* Close a blocks db. */
  void uninm_blocks_db_close (uninm_blocks_db handle);

  /* Retrieve the name of a Unicode codepoint. The string must not
     be freed by the caller. */
  const char *uninm_name (uninm_names_db handle, unsigned int codepoint);

  /* Retrieve the annotation of a Unicode codepoint. The string must
     not be freed by the caller. */
  const char *uninm_annotation (uninm_names_db handle,
                                unsigned int codepoint);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus              /* C++ bindings */

#include <exception>

namespace libunicodenames
{

  class unicodenames_exception:public std::exception
  {
    virtual const char *what () throw ();
  };

  class memory_exhausted:public unicodenames_exception
  {
    virtual const char *what () throw ();
  };

  class open_failed:public unicodenames_exception
  {
    virtual const char *what () throw ();
  };

  char *find_names_db (const char *locale_base = 0);
  char *find_blocks_db (const char *locale_base = 0);

  class unicodenames
  {
  private:
    uninm_names_db db;

  public:
    unicodenames (const char *filename);
     ~unicodenames ();

    const char *name (unsigned int codepoint)
    {
      return uninm_name (db, codepoint);
    }

    const char *annotation (unsigned int codepoint)
    {
      return uninm_annotation (db, codepoint);
    }
  };                            /* class unicodenames */

};                              /* namespace libunicodenames */

#endif /* __cplusplus */

#endif /* _LIBUNICODENAMES_H */

/* local variables:    */
/* c-file-style: "gnu" */
/* end:                */
