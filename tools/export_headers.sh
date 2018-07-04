#!/bin/sh
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

rootdir=${1}
chromiumdir=$rootdir/${2}/chromium-${3}
outdir=$rootdir/${4}

if [ ! -e ${outdir} ]; then
    echo "** Unable to export headers :"
    echo -e "\t$outdir does not exist"
    exit 1
elif [ ! -d ${outdir} ]; then
    echo "** Unable to export headers :"
    echo -e "\t$outdir is not a directory"
    exit 1
fi

echo "** Exporting eglcontent headers"

if [ -d ${outdir}/eglcontent ]; then
    rm -rf ${outdir}/eglcontent
elif [ -e ${outdir}/eglcontent ]; then
    echo "** Unable to export headers :"
    echo -e "\t$outdir/eglcontent is not a directory"
    exit 1
fi

mkdir -p ${outdir}/eglcontent

find ${rootdir}/src/api -name '*.h' -exec cp {} ${outdir}/eglcontent \;

FILES=`find ${outdir}/eglcontent -name '*.h'`
for f in $FILES; do
    sed -i 's/#include "third_party\/khronos\/\(.*\)"$/#include <\1>/g' $f
done
