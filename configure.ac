# **************************************************************************
# SoWin/configure.in

m4_define([SOWIN_MAJOR], [0])
m4_define([SOWIN_MINOR], [9])
m4_define([SOWIN_MICRO], [99])
m4_define([SOWIN_BETA],  [])
m4_define([SOWIN_VERSION_STRING],
          [SOWIN_MAJOR.SOWIN_MINOR.SOWIN_MICRO[]SOWIN_BETA])

m4_define([SOWIN_ABI_CURRENT],  [m4_eval((SOWIN_MAJOR*20)+SOWIN_MINOR)])
m4_define([SOWIN_ABI_REVISION], [SOWIN_MICRO])
m4_define([SOWIN_ABI_AGE],      [SOWIN_MINOR])

# **************************************************************************
AC_INIT([SoWin], [SOWIN_VERSION_STRING], [coin-bugs@coin3d.org])

AC_CONFIG_SRCDIR([src/Inventor/Win/SoWin.cpp])
AC_CONFIG_AUX_DIR([cfg])

# FIXME: using SoWin on top of SGI and / or TGS Inventor is simply an
# un-implemented feature yet. 20020103 mortene.
if test x"${with_inventor+set}" = x"set"; then
  AC_MSG_ERROR([SoWin has not been tuned for linking against non-Coin Inventor implementations yet])
fi

# **************************************************************************

AC_CANONICAL_SYSTEM

SIM_AC_MSVC_DSP_ENABLE_OPTION

AC_ARG_ENABLE([msvc],
  [AC_HELP_STRING([--disable-msvc], [don't require MS Visual C++ on Cygwin])],
  [case $enableval in
  no | false) sim_ac_try_msvc=false ;;
  *)          sim_ac_try_msvc=true ;;
  esac],
  [sim_ac_try_msvc=true])

if $sim_ac_try_msvc; then
  SIM_AC_SETUP_MSVC_IFELSE([], [
    case $host in
    *-cygwin) SIM_AC_ERROR([no-msvc++]) ;;
    esac
  ])
fi

# **************************************************************************
# Library versioning. For information about our versioning strategy, see the
# document ``HACKING'' in the Coin CVS module.

AC_SUBST([SOWIN_MAJOR_VERSION], [SOWIN_MAJOR])
AC_SUBST([SOWIN_MINOR_VERSION], [SOWIN_MINOR])
AC_SUBST([SOWIN_MICRO_VERSION], [SOWIN_MICRO])
AC_SUBST([SOWIN_VERSION], [SOWIN_VERSION_STRING])
VERSION=$SOWIN_VERSION

# Libtool versioning
AC_SUBST([LT_CURRENT], [SOWIN_ABI_CURRENT])
AC_SUBST([LT_REVISION], [SOWIN_ABI_REVISION])
AC_SUBST([LT_AGE], [SOWIN_ABI_AGE])

AC_DEFINE_UNQUOTED(SOWIN_MAJOR_VERSION, $SOWIN_MAJOR_VERSION,
  [Define to the major version of SoWin])
AC_DEFINE_UNQUOTED(SOWIN_MINOR_VERSION, $SOWIN_MINOR_VERSION,
  [Define to the minor version of SoWin])
AC_DEFINE_UNQUOTED(SOWIN_MICRO_VERSION, $SOWIN_MICRO_VERSION,
  [Define to the micro version of SoWin])
AC_DEFINE_UNQUOTED(SOWIN_VERSION, "$SOWIN_VERSION",
  [Version string for SoWin])

# **************************************************************************

sowin_build_dir=`pwd`
sowin_src_dir=`cd "$srcdir"; pwd`
sowin_w32_build_dir=`cygpath -w "$sowin_build_dir" 2>/dev/null || echo "$sowin_build_dir"`
sowin_w32_src_dir=`cygpath -w "$sowin_src_dir" 2>/dev/null || echo "$sowin_src_dir"`

# **************************************************************************
#  Locate C++ compiler and set C++ as the default language to use
#  in tests. The configure script will automatically terminate if
#  it doesn't find a C++ compiler.

AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX

AC_OBJEXT
AC_EXEEXT

# moved below AC_PROG_CC so -g is preserved in $C[XX]FLAGS - 20020521 mortene
if $BUILD_WITH_MSVC; then
  SIM_AC_SETUP_MSVCRT([
    CPPFLAGS="$CPPFLAGS $sim_ac_msvcrt_CPPFLAGS"
    CFLAGS="$CFLAGS $sim_ac_msvcrt_CFLAGS"
    CXXFLAGS="$CXXFLAGS $sim_ac_msvcrt_CXXFLAGS"
    LDFLAGS="$LDFLAGS $sim_ac_msvcrt_LDFLAGS"
    LIBS="$LIBS $sim_ac_msvcrt_LIBS"
    # sim_ac_msvcrt_LIBLIBS is set up at the end
    # sim_ac_msvcrt_LIBLDFLAGS is set up at the end
    LDFLAGS="$LDFLAGS $sim_ac_msvcrt_LIBLDFLAGS"
    LIBS="$LIBS $sim_ac_msvcrt_LIBLIBS"
    AC_SUBST([SOGUI_MSVC_LIBC], [$sim_ac_msvcrt])
  ])
fi

# **************************************************************************

AM_INIT_AUTOMAKE(SoWin, $SOWIN_VERSION)

AM_CONFIG_HEADER([src/config.h])

AM_DISABLE_STATIC
AM_MAINTAINER_MODE

# don't use CygWin's ranlib on static library
if $BUILD_WITH_MSVC; then
  RANLIB=true
  export RANLIB
fi

AC_PROG_LIBTOOL

# These are used for constructing the sowin-config file.
AC_SUBST([SOGUI_EXTRA_CPPFLAGS], [$CPPFLAGS])
AC_SUBST([SOGUI_EXTRA_CFLAGS], [$CFLAGS])
AC_SUBST([SOGUI_EXTRA_CXXFLAGS], [$CXXFLAGS])
AC_SUBST([SOGUI_EXTRA_LDFLAGS], [$LDFLAGS])
AC_SUBST([SOGUI_EXTRA_LIBS], [$LIBS])

if $sim_ac_build_library; then

# **************************************************************************
# Header files we might want.

AC_CHECK_HEADERS([windows.h tlhelp32.h unistd.h sys/types.h sys/time.h X11/extensions/SGIMisc.h X11/Xproto.h X11/extensions/XInput.h netinet/in.h])

# *******************************************************************
# Instead of getenv() on most Win32 platforms (not Windows CE).

AC_MSG_CHECKING([for GetEnvironmentVariable() function])
AC_TRY_LINK([#include <windows.h>],
            [(void)GetEnvironmentVariable("FOOBAR", NULL, 0);],
  [AC_MSG_RESULT([yes])
  AC_DEFINE([HAVE_GETENVIRONMENTVARIABLE],1, [Define to use GetEnvironmentVariable() instead of getenv()])],
  [AC_MSG_RESULT([no])])

# *******************************************************************
# Win32 LoadLibrary() and friends available? (Used for Win32-specific
# debugging code).

SIM_AC_CHECK_LOADLIBRARY(
  AC_DEFINE([HAVE_WIN32_LOADLIBRARY], 1, [Define to use Win32 LoadLibrary()])
)

# **************************************************************************
# Compiler control.

SIM_AC_COMPILE_DEBUG(
  [CPPFLAGS="$CPPFLAGS -DSOWIN_DEBUG=1"],
  [CPPFLAGS="$CPPFLAGS -DSOWIN_DEBUG=0"])

SIM_AC_CHECK_VAR_FUNCTIONNAME

SIM_AC_DEBUGSYMBOLS
SIM_AC_RTTI_SUPPORT
SIM_AC_EXCEPTION_HANDLING
SIM_AC_PROFILING_SUPPORT
SIM_AC_COMPILER_WARNINGS

# This is at least used to allow static compilation on Cygwin + MSWindows
# without hitting the SOWIN_DLL / SOWIN_NOT_DLL safety check.
CPPFLAGS="$CPPFLAGS -DSOWIN_INTERNAL"

SIM_AC_SOGUI_STATIC_DEFAULTS

fi

# **************************************************************************
# Variable substitutions for using libSoWin in the generic code.

AC_SUBST([Gui], [Win])
AC_SUBST([gui], [win])
AC_SUBST([GUI], [WIN])
AC_SUBST([WIDGET], [HWND])
AC_SUBST([EVENT], ["MSG *"])
AC_SUBST([COMPONENTHEADER], [])

# **************************************************************************

sim_ac_perl_exe=false
# FIXME

# path_tag is used to identify paths in docs/coin.doxygen that needs to be
# transformed using cygpath under cygwin.

case $host in
*-cygwin) path_tag="<PATH>" ;;
*)        path_tag= ;;
esac
   
AC_SUBST(path_tag)

sim_ac_makensis_exe=false
case $host in
*-cygwin)
  AC_PATH_PROG([sim_ac_makensis_exe], [makensis], [false], [$PATH])
  ;;
esac
   
sim_ac_windows_packagable=true
if test x"$sim_ac_perl_exe" = xfalse || test x"$sim_ac_makensis_exe" = xfalse; then
  sim_ac_windows_packageable=false
fi
 
AM_CONDITIONAL([WIN_PACKAGEABLE], $sim_ac_windows_packageable)

# **************************************************************************
# it is important that $CONFIG is set up before the Coin detection is run...

AC_ARG_WITH(
  [alternate],
  [AC_HELP_STRING([--with-alternate=string],
                  [specify name of alternate configuration])],
  [CONFIG=$withval],
  [CONFIG=default])

AC_SUBST(CONFIG)

AC_ARG_WITH(
  [suffix],
  [AC_HELP_STRING([--with-suffix=string],
                  [specify library name suffix (e.g. "d" for debug)])],
  [SUFFIX=$withval],
  [SUFFIX=])

AC_SUBST(SUFFIX)

# **************************************************************************

AM_CONDITIONAL([MAC_FRAMEWORK], [false])

SIM_AC_SOGUI_SETUP_DOXYGEN(SoWin)

# **************************************************************************

AC_ARG_WITH(
  [alternate],
  [AC_HELP_STRING([--with-alternate=string],
                  [specify name of alternate configuration])],
  [CONFIG=$withval],
  [CONFIG=default])

AC_SUBST(CONFIG)

AC_ARG_WITH(
  [suffix],
  [AC_HELP_STRING([--with-suffix=string],
                  [specify library name suffix (e.g. "_g")])],
  [SUFFIX=$withval],
  [SUFFIX=])

AC_SUBST(SUFFIX)

# **************************************************************************

sim_ac_build_library=true
AC_ARG_ENABLE(
  [build],
  [AC_HELP_STRING([--disable-build], [disable configuring for library build])],
  [case $enableval in
    no | false) sim_ac_build_library=false ;;
  esac])

if $sim_ac_build_library; then
# **************************************************************************

AM_CONDITIONAL(BUILD_LIBRARY, $sim_ac_build_library)

# **************************************************************************
# Will naturally always be false for SoWin.

AM_CONDITIONAL(BUILD_METAFILES, false)
AM_CONDITIONAL(HAVE_JOYSTICK_LINUX, false)

# **************************************************************************
# Search for and set up stuff we depend on.

AC_CHECK_HEADERS([GL/gl.h OpenGL/gl.h GL/glu.h OpenGL/glu.h])

# check for Coin library and its dependencies

SIM_AC_HAVE_COIN_IFELSE([
  CPPFLAGS="$CPPFLAGS $sim_ac_coin_cppflags"
  LDFLAGS="$LDFLAGS $sim_ac_coin_ldflags"
  LIBS="$sim_ac_coin_libs $LIBS"
  SOGUI_EXTRA_CPPFLAGS="$SOGUI_EXTRA_CPPFLAGS $sim_ac_coin_cppflags"
  SOGUI_EXTRA_LDFLAGS="$SOGUI_EXTRA_LDFLAGS $sim_ac_coin_ldflags"
  SOGUI_EXTRA_LIBS="$sim_ac_coin_libs $SOGUI_EXTRA_LIBS"
], AC_MSG_ERROR(couldn't compile and link against Coin))

## FIXME: make it possible to build SoWin on top of SGI Inventor.
## 20011007 mortene.

# **************************************************************************
# misc implementation-dependent Open Inventor features

# One or more of the macros used above is buggy and doesn't reset
# from C to C++ mode.  The AC_LANG(C++) reset below is a work-around.
# FIXME: should of course smoke out the offender and fix that instead
# of just hiding the bug. 20011012 mortene.
AC_LANG(C++)

SIM_AC_HAVE_INVENTOR_NODE(SoPolygonOffset)

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for SoKeyboardEvent::DELETE enum],
  [#include <Inventor/events/SoKeyboardEvent.h>], [
   /* This is either DELETE or KEY_DELETE */
   SoKeyboardEvent::Key key = SoKeyboardEvent::DELETE;],
  [HAVE_SOKEYBOARDEVENT_DELETE])

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for SoMouseButtonEvent::BUTTON5 enum],
  [#include <Inventor/events/SoMouseButtonEvent.h>], [
   /* mouse wheel support needs BUTTON4 and BUTTON5 */
   SoMouseButtonEvent::Button button = SoMouseButtonEvent::BUTTON5;],
  [HAVE_SOMOUSEBUTTONEVENT_BUTTON5])

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for SoCamera::setStereoMode() function],
  [#include <Inventor/nodes/SoPerspectiveCamera.h>], [
   /* SoCamera is abstract, so test with SoPerspectiveCamera */
   SoPerspectiveCamera * c = new SoPerspectiveCamera;
   c->setStereoMode(SoCamera::MONOSCOPIC);],
  [HAVE_SOCAMERA_SETSTEREOMODE])

# **************************************************************************
# Misc set-up.

SIM_EXPAND_DIR_VARS

# Functions from the gdi32.lib and user32.lib libraries are used.
LIBS="$LIBS -lgdi32 -luser32"
SOGUI_EXTRA_LIBS="$SOGUI_EXTRA_LIBS -lgdi32 -luser32"

# **************************************************************************

fi

AC_SUBST([soqt_build_dir])
AC_SUBST([soqt_src_dir])
AC_SUBST([soqt_w32_build_dir])
AC_SUBST([soqt_w32_src_dir])

# **************************************************************************
# Remove redundant options from certain option lists.

SIM_AC_UNIQIFY_LIST(SOGUI_EXTRA_CPPFLAGS, -I$includedir $SOGUI_EXTRA_CPPFLAGS)
SIM_AC_UNIQIFY_LIST(SOGUI_EXTRA_LDFLAGS, -L$libdir $SOGUI_EXTRA_LDFLAGS)
SIM_AC_UNIQIFY_LIST(SOGUI_EXTRA_LIBS, $SOGUI_EXTRA_LIBS)

SIM_AC_UNIQIFY_LIST(CPPFLAGS, $CPPFLAGS)
SIM_AC_UNIQIFY_LIST(LDFLAGS, $LDFLAGS)
SIM_AC_UNIQIFY_LIST(LIBS, $LIBS)

SOWIN_STATIC=false

if test x${enable_shared+set} = xset; then
  case $enable_shared in
  yes | true)  SOWIN_STATIC=false ;;
  *)           SOWIN_STATIC=true ;;
  esac
fi

if test x${enable_static+set} = xset; then
  case $enable_static in
  yes | true)  SOWIN_STATIC=true ;;
  *)           SOWIN_STATIC=false ;;
  esac
fi

AC_SUBST([LIBFLAGS], [])

# **************************************************************************
# Remaining setup based on platform.

AM_CONDITIONAL(BUILD_WITH_MSVC, $BUILD_WITH_MSVC)

if $sim_ac_build_library; then
if $BUILD_WITH_MSVC; then
  rm -f vc60.pdb
  ## Ensure that if we link with Coin, we use the same C library as Coin
  if test x"$sim_ac_coin_msvcrt" != x"" &&
     test x"$sim_ac_msvcrt" != x"$sim_ac_coin_msvcrt"; then
      SIM_AC_CONFIGURATION_WARNING([You have built Coin with the $sim_ac_coin_msvcrt C library, while you try to build So$Gui with the $sim_ac_msvcrt C library.  This can cause mysterious crashes for you.  We recommend that you run So$Gui's configure script with the --with-msvcrt=$sim_ac_coin_msvcrt option.])
  fi
  LIBFLAGS="$LIBFLAGS $sim_ac_msvcrt_LIBLDFLAGS"
  LIBS="$LIBS $sim_ac_msvcrt_LIBLIBS"

  if $SOWIN_STATIC; then
    SOGUI_EXTRA_CPPFLAGS="$SOGUI_EXTRA_CPPFLAGS -DSOWIN_NOT_DLL"
  else
    CPPFLAGS="-DSOWIN_MAKE_DLL $CPPFLAGS"
    SOGUI_EXTRA_CPPFLAGS="$SOGUI_EXTRA_CPPFLAGS -DSOWIN_DLL"
  fi

  debugfile="`pwd`/src/Inventor/Win/sowin${SOWIN_MAJOR_VERSION}${SUFFIX}.pdb"
  debugfile=`cygpath -w "$debugfile" | sed 's,\\\\,\\\\\\\\,g'`
  if $SOWIN_STATIC; then
    SIM_AC_CONFIGURATION_SETTING([SoWin build type], [static .lib])
    LIBFLAGS="-LIB $LIBFLAGS"
    LIBFLAGS="$LIBFLAGS /OUT:sowin$SOWIN_MAJOR_VERSION$SUFFIX.lib"
  else
    LIBFLAGS="-DLL /INCREMENTAL:NO $LIBFLAGS"
    case $enable_symbols in
    no | false)
      SIM_AC_CONFIGURATION_SETTING([SoWin build type],
                                   [dynamic .dll, no symbols])
      LIBFLAGS="$LIBFLAGS /RELEASE"
      ;;
    *)
      SIM_AC_CONFIGURATION_SETTING([SoWin build type], [dynamic .dll + .pdb])
      CFLAGS="/Fd$debugfile $CFLAGS"
      CXXFLAGS="/Fd$debugfile $CXXFLAGS"
      LIBFLAGS="$LIBFLAGS /DEBUG /PDB:sowin$SOWIN_MAJOR_VERSION$SUFFIX.pdb"
      ;;
    esac
    LIBFLAGS="$LIBFLAGS /OUT:sowin$SOWIN_MAJOR_VERSION$SUFFIX.dll"
  fi
  SIM_AC_CONFIGURATION_SETTING([C library version], [$sim_ac_msvcrt])

  # We use a version suffix on the .dll-file, so several incompatible
  # (major) versions can be installed on a system.
  #
  # BTW, when linking DLLs, the 3rd-party .lib files will be
  # linked into the .dll file. I believe it is still advisable to
  # list all libs used upon `sowin-config --libs`, as we can then
  # also use them from "parent" code (remember that their interfaces
  # is not exposed from the DLL) without any fuss.
  SOGUI_EXTRA_LIBS="-lsowin$SOWIN_MAJOR_VERSION$SUFFIX $SOGUI_EXTRA_LIBS"
  win_srcdir=`cd $srcdir; pwd`
  win_srcdir=`cygpath -w "$srcdir" | sed 's,\\\\,\\\\\\\\,g'`
  AC_SUBST(win_srcdir)
else
  SOGUI_EXTRA_LIBS="-lSoWin $SOGUI_EXTRA_LIBS"

  # For the build/sowin.spec RPM specification file.
  SIM_AC_ISO8601_DATE(sowin_configure_date)
  AC_SUBST(sowin_configure_date)
fi

  COIN_COMPILER="$CXX"
  if $BUILD_WITH_MSVC; then
    COIN_COMPILER="wrapmsvc"
  fi
  AC_SUBST(COIN_COMPILER)

else
  SIM_AC_CONFIGURATION_SETTING([SoWin build type], [build disabled])
fi

SIM_AC_MSVC_DSP_SETUP([SOWIN], [SoWin], [sowin], [-I$sowin_build_dir/src -I$sowin_build_dir/data -I$sowin_src_dir/src])

# **************************************************************************
# Submodules that needs to be configured...

# Material editor(s) not part of the public API yet, so there's
# no point yet in installing the material data.
# AC_CONFIG_SUBDIRS(data)

# **************************************************************************
# finally generate all the directories, makefiles, autogenerated
# sourcefiles, and config headers.
#
# Note that sowin-$CONFIG.cfg needs to be generated from the configure
# script -- not just from the Makefile -- as the data/configure script
# depends on it. (data/configure is temporarily disabled, BTW, but anyway..)

AC_OUTPUT([
	sowin-$CONFIG.cfg:src/Inventor/Win/common/sogui.cfg.in
	Makefile
	src/Makefile
	src/Inventor/Makefile
	src/Inventor/Win/Makefile
	src/Inventor/Win/devices/Makefile
	src/Inventor/Win/widgets/Makefile
	src/Inventor/Win/viewers/Makefile
	man/Makefile
	man/man1/Makefile
	man/man3/Makefile
	html/Makefile
])

if $sim_ac_build_library; then
  SIM_AC_CONFIGURATION_SETTING([Installation Prefix], [$prefix])
fi

SIM_AC_CONFIGURATION_SUMMARY

if $sim_ac_build_library; then
  echo ""
  echo "Now, run 'make install' to build and install."
  echo ""
else
  echo ""
fi

# **************************************************************************
