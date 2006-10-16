#! /bin/sh
#
# This script generates the Visual Studio 6 build files for Windows.
#
# 20041214 larsa

rm -f sowin1.dsp sowin1.dsw sowin1.vcproj sowin1.sln install-headers.bat

build_pwd=`pwd`
build="`cygpath -w $build_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"
build_pwd="`pwd | sed -e 's/\\//\\\\\\\\/g'`\\\\"

source_pwd=`cd ../..; pwd`
source="`cygpath -w $source_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"
source_pwd="`(cd ../..; pwd) | sed -e 's/\\//\\\\\\\\/g'`"

../../configure --with-msvcrt=mtd --with-suffix=d \
  --enable-debug --enable-symbols || exit 1
cp src/config.h src/config-debug.h

../../configure --enable-msvcdsp --with-msvcrt=mt \
  --disable-debug --disable-symbols --enable-optimization || exit 1
cp src/config.h src/config-release.h

cp config-wrapper.h src/config.h

make || exit 1

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e 's/COIN_DLL/COIN_NOT_DLL/g' \
  -e '/_MAKE_DLL/ { s/COIN_NOT_DLL/COIN_DLL/g; }' \
  -e 's/$/\r/g' \
  <sowin1.dsp >new.dsp

mv new.dsp sowin1.dsp

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e 's/$/\r/g' \
  <install-headers.bat >new.bat

mv new.bat install-headers.bat

find . -name "moc_*"
ls config.h 2>/dev/null

echo "Done."
echo "Modify so the static configurations are built with COIN_NOT_DLL"
echo "Then make sure there are no absolute paths in the project files"
grep -i c: sowin1.dsp sowin1.dsw
echo "Run 'devenv sowin1.dsw' and save all solution files."

# only needed with post-build events:
# echo "Then run './fixvcproj.sh'."

# How can I avoid the modal upgrade prompt-dialog for MSVC8 here???
# devenv /command "File.OpenProject $build\\sowin1.dsp"

