#! /bin/sh
#
# This script generates the Visual Studio 6 build files for Windows.
#
# 20041214 larsa

rm -f sowin1.dsp sowin1.dsw sowin1.vcproj sowin1.sln \
      sowin1_install.dsp sowin1_install.dsw \
      sowin1_install.vcproj sowin1_install.sln \
      sowin1_uninstall.dsp sowin1_uninstall.dsw \
      sowin1_uninstall.vcproj sowin1_uninstall.sln \
      ../misc/install-headers.bat ../misc/uninstall-headers.bat

build_pwd=`pwd`
build="`cygpath -w $build_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"
build_pwd="`pwd | sed -e 's/\\//\\\\\\\\/g'`\\\\"

source_pwd=`cd ../..; pwd`
source="`cygpath -w $source_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"
source_pwd="`(cd ../..; pwd) | sed -e 's/\\//\\\\\\\\/g'`"

../../configure --with-msvcrt=mtd --with-suffix=d \
  --enable-debug --enable-symbols || exit 1
mv src/config.h src/config-debug.h

../../configure --enable-msvcdsp --with-msvcrt=mt \
  --disable-debug --disable-symbols --enable-optimization || exit 1
mv src/config.h src/config-release.h

cp ../misc/config-wrapper.h src/config.h

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
  <../misc/install-headers.bat >new.bat

mv new.bat ../misc/install-headers.bat

echo "Done."
echo "Modify so the static configurations are built with COIN_NOT_DLL"
echo "Then make sure there are no absolute paths in the project files"
grep -i c: sowin1.dsp sowin1.dsw

# find . -name "moc_*" | xargs rm

# How can I avoid the modal upgrade prompt-dialog for MSVC7.1 here???
# devenv /command "File.OpenProject $build\\sowin1.dsp"

