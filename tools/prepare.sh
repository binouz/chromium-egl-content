#!/bin/bash

if [ -z ${1} ] || [ -z ${2} ] || [ -z ${3} ]; then
    echo "Usage : ${0} CEC_DIR CHROMIUM_DIR CHROMIUM_VERSION"
    echo -e "\tCEC_DIR : Path to chromium-egl-content"
    echo -e "\tCHROMIUM_DIR : Name of directory with chromium checkout under CEC_DIR"
    echo -e "\tCHROMIUM_VERSION : Chromium version to prepare"
    exit 1
fi

topdir=${1}
patchdir=${topdir}/patches
sourcedir=${topdir}/${2}/chromium-${3}

pushd ${sourcedir}
echo "** Apply chromium patches"
for file in `ls ${patchdir} | sort`; do
    patch -p1 < ${patchdir}/${file}
done
popd > /dev/null

echo "** Installing eglcontent symlinks in chromium tree"
if [ -d ${sourcedir}/content/eglcontent ]; then
    rm -rf ${sourcedir}/content/eglcontent
fi
mkdir ${sourcedir}/content/eglcontent
ln -s ${topdir}/src/build/BUILD.gn ${sourcedir}/content/eglcontent
ln -s ${topdir}/src/build/egl_content.gni ${sourcedir}/content/eglcontent
ln -s ${topdir}/src/api ${sourcedir}/content/eglcontent
ln -s ${topdir}/src/content ${sourcedir}/content/eglcontent
ln -s ${topdir}/src/browser ${sourcedir}/content/eglcontent
ln -s ${topdir}/src/renderer ${sourcedir}/content/eglcontent
ln -s ${topdir}/src/ozone ${sourcedir}/ui/ozone/platform/eglcontent
