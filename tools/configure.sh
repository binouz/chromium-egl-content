#!/bin/bash

if [ -z ${1} ] || [ -z ${2} ] || [ -z ${3} ] || [ -z ${4} ]; then
    echo "Usage : ${0} CEC_DIR CHROMIUM_DIR CHROMIUM_VERSION OUT_DIR"
    echo -e "\tCEC_DIR : Path to chromium-egl-content"
    echo -e "\tCHROMIUM_DIR : Name of directory with chromium checkout under CEC_DIR"
    echo -e "\tCHROMIUM_VERSION : Chromium version to prepare"
    echo -e "\tOUT_DIR : Name of output build directory"
    exit 1
fi

topdir=${1}
chromiumdir=${topdir}/${2}/chromium-${3}
outdir=${topdir}/${4}

if [ ! -d ${outdir} ]; then
    if [ -e ${outdir} ]; then
	echo "** Unable to configure build :"
	echo -e "\t$outdir already exists and is not a directory"
    fi
    mkdir -p ${outdir}
fi

echo "** Copying build args"
cp ${topdir}/src/build/args.gn ${outdir}

echo "** Adding GN_EXTRA_ARGS to build args"
if [ -n ${GN_EXTRA_ARGS} ]; then
    echo ${GN_EXTRA_ARGS} >> ${outdir}/args.gn
fi

echo "** Creating build files"
pushd ${chromiumdir} > /dev/null
export CHROMIUM_BUILDTOOLS_PATH=${chromiumdir}/buildtools/
gn gen ${outdir}
popd > /dev/null
