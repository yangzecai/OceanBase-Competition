CUR_DIR="$( cd "$( dirname "$0"  )" && pwd  )"
cd ${CUR_DIR}

if [ ! -d "build" ]; then
    mkdir build
fi
cd build/
cmake .. -DDEBUG=ON

tmp=$?
if [ ${tmp} -ne 0 ]
then
    exit -1
fi

make -j

tmp=$?
if [ ${tmp} -ne 0 ]
then
    exit -1
fi