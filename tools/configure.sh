#!/bin/bash
# Copyright 2018 Aubin REBILLAT
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
if [ -n "${GN_EXTRA_ARGS}" ]; then
    for arg in ${GN_EXTRA_ARGS}; do
        echo $arg >> ${outdir}/args.gn
    done
fi

echo "** Creating build files"
pushd ${chromiumdir} > /dev/null
export CHROMIUM_BUILDTOOLS_PATH=${chromiumdir}/buildtools/
gn gen ${outdir}
popd > /dev/null
