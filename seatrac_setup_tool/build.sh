
if [ $# -eq 1 ]
    then
        export CMAKE_PREFIX_PATH=$1:\$CMAKE_PREFIX_PATH
fi

mkdir build
cd build

cmake ..
make

cd ..
