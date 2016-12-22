#!/bin/bash

if [ -z ${1} ] || [ -z ${2} ] || [ -z ${3} ]; then
    echo "Usage : ${0} CEC_DIR OUT_DIR CHROMIUM_VERSION"
    echo -e "\tCEC_DIR : Path to chromium-egl-content directory"
    echo -e "\tOUT_DIR : Name of the directory to create under CEC_DIR"
    echo -e "\tCHROMIUM_VERSION : Chromium version to prepare"
    exit 1
fi

outdir=${1}/${2}
src_url=http://commondatastorage.googleapis.com/chromium-browser-official/
tarball=chromium-${3}.tar.xz
sourcedir=${outdir}/chromium-${3}

if [ ! -d ${outdir} ]; then
    if [ -e ${outdir} ]; then
	echo "** Unable to download chromium sources :"
	echo -e "\t${outdir} already exists and is not a directory"
	exit 1
    fi
    mkdir -p ${outdir}
fi

if [ ! -f ${outdir}/${tarball} ]; then
    if [ -e ${outdir}/${tarball} ]; then
	echo "** Unable to download chromium sources :"
	echo -e "\t${outdir}/${tarball} already exists and is not a directory"
    fi
    echo "** Downloading chromium sources to $outdir"
    pushd ${outdir} > /dev/null
    wget ${src_url}${tarball}
    popd > /dev/null
else
    echo "** Chromium sources already downloaded"
fi

echo "** Unpacking tarball"
if [ -e ${sourcedir} ]; then
    rm -rf ${sourcedir}
fi
pushd ${outdir} > /dev/null
tar -xvf ${tarball}
popd > /dev/null

echo "** Downloading chromium gn"
download_from_google_storage --no_resume --platform=linux* --no_auth --bucket chromium-gn -s ${sourcedir}/buildtools/linux64/gn.sha1
