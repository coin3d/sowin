#!/bin/sh
############################################################################

moduledir=${0%/[^/]*}
module=${moduledir##*/}
GUI=`echo $module | cut -c3-`
cvs2cl=$HOME/code/cvs/src/cvs2cl/cvs2cl.pl
headerfile=/tmp/$module.header

cd $moduledir

############################################################################
cat > $headerfile <<ENDOFHEADER
ChangeLog
=========

This is the ChangeLog file for the $module module.  This file is automatically
generated every night.  Entries are in reversed chronological order.  Check
also out the following ChangeLog files:

  ./cfg/m4/ChangeLog
  ./src/Inventor/Win/common/ChangeLog

See http://www.red-bean.com/~kfogel/cvs2cl.shtml for information about the
cvs2cl script used to generate this file.

============================================================================

ENDOFHEADER
############################################################################

cvs update -dP

cvs log | $cvs2cl --stdin --header $headerfile --separate-header --prune \
  --ignore 'ChangeLog$' \
  --ignore '(Makefile\.in|configure|aclocal\.m4|config\.sub|config\.guess)$' \
  --ignore '(ltconfig|ltmain\.sh|missing|mkinstalldirs|stamp-h.*|install-sh)$' \
  --ignore 'config\.h\.in$' \
  --ignore 'cfg/m4' \
  --ignore 'src/Inventor/Win/common' \
  --ignore 'data' \
  --ignore 'examples' 

rm ChangeLog.bak $headerfile

cvs commit -m "Automatic ChangeLog generation" ChangeLog

