#! /bin/sh
#
# This script generates the Visual Studio 6 build files for Windows.
#
# 20041214 larsa

rm -f sowin1.dsp sowin1.dsw installsowinheaders.bat

../../configure --enable-msvcdsp --with-msvcrt=mt || exit 1
make

build_pwd=`pwd`
build="`cygpath -w $build_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"
source_pwd=`cd ../..; pwd`
source="`cygpath -w $source_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"

# cp sowin1.dsp orig.dsp

sed \
  -e "s/$build/./g" \
  -e "s/$source/..\\\\../g" \
  -e 's/$/\r/g' \
  <sowin1.dsp >new.dsp
mv new.dsp sowin1.dsp

# How can I avoid the modal upgrade prompt-dialog for MSVC7.1 here???
# devenv /command "File.OpenProject $build\\sowin1.dsp"

