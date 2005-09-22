/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOWIN_INTERNALDEFS_H
#define SOWIN_INTERNALDEFS_H

/* ********************************************************************** */

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

/* ********************************************************************** */

#ifdef __FILE__
#define SOWIN_STUB_FILE __FILE__
#else
/* FIXME: avoid this case by redefining the compilation rules to define the
   current filename in some variable.  [20010919 larsa] */
#define SOWIN_STUB_FILE ((char *)0L)
#endif

#ifdef __LINE__
#define SOWIN_STUB_LINE __LINE__
#else
#define SOWIN_STUB_LINE 0
#endif

#ifdef __cplusplus
#ifdef HAVE_CPP_COMPILER_FUNCTION_NAME_VAR
#define SOWIN_STUB_FUNC HAVE_CPP_COMPILER_FUNCTION_NAME_VAR
#else
#define SOWIN_STUB_FUNC ((const char *)0L)
#endif
#else /* !__cplusplus */
#ifdef HAVE_C_COMPILER_FUNCTION_NAME_VAR
#define SOWIN_STUB_FUNC HAVE_C_COMPILER_FUNCTION_NAME_VAR
#else
#define SOWIN_STUB_FUNC ((const char *)0L)
#endif
#endif /* !__cplusplus */

#if SOWIN_DEBUG

#include <Inventor/errors/SoDebugError.h>

/*
  This stupid thing is here to silence some compilers that complain on
  constant if-expressions.
*/

inline int sowin_not_null(const void * arg) { return (arg != NULL) ? 1 : 0; }


/* Collects common code from SOWIN_STUB(), SOWIN_STUB()_ONCE and
   SOWIN_OBSOLETED(). */

#define SOWIN_FUNCTIONIDENTIFIER(SOWINSTR) \
    SbString SOWINSTR(sowin_not_null(SOWIN_STUB_FILE) ? SOWIN_STUB_FILE : ""); \
    if (SOWINSTR.getLength() > 0) { SOWINSTR += ':'; } \
    SOWINSTR += SbString((int)SOWIN_STUB_LINE); SOWINSTR += ':'; \
    SOWINSTR += sowin_not_null(SOWIN_STUB_FUNC) ? SOWIN_STUB_FUNC : ""

/*
  SOWIN_STUB(): a macro that prints out stub information.
  Used where there is functionality missing.
*/

#define SOWIN_STUB() \
  do { \
    SOWIN_FUNCTIONIDENTIFIER(s); \
    SoDebugError::postWarning(s.getString(), \
                              "STUB: functionality not yet completed"); \
  } while (0)

/*
  SOWIN_STUB_ONCE(): a macro that prints out stub information, but only on
  the first pass.  Used where there is functionality missing that may be
  called hundreds of times.
*/

#define SOWIN_STUB_ONCE() \
  do { \
    static int first = 1; \
    if (first) { \
      SOWIN_FUNCTIONIDENTIFIER(s); \
      SoDebugError::postWarning(s.getString(), \
                                "STUB: functionality not yet completed " \
                                "(first and last warning)"); \
      first = 0; \
    } \
  } while (0)

/*
  SOWIN_OBSOLETED(): a macro that prints out information about an obsoleted
  function still being in use.
*/

#define SOWIN_OBSOLETED() \
  do { \
    SOWIN_FUNCTIONIDENTIFIER(s); \
    SoDebugError::post(s.getString(), \
                       "OBSOLETED: functionality no longer supported"); \
  } while (0)

#else /* !SOWIN_DEBUG */

/* snub the stubs */
#define SOWIN_STUB()      do { } while (0)
#define SOWIN_STUB_ONCE() do { } while (0)
#define SOWIN_OBSOLETED() do { } while (0)

#endif /* !SOWIN_DEBUG */

/*
  GETTEXT support
*/

#if defined(ENABLE_NLS) && defined(HAVE_GETTEXT)
#include <libintl.h>
#define _(String) dgettext (PACKAGE, String)
#define N_(String) (String)
#else
#define _(String) (String)
#define N_(String) (String)
#endif /* HAVE_GETTEXT && ENABLE_NLS */

/* ********************************************************************** */

#endif /* ! SOWIN_INTERNALDEFS_H */
