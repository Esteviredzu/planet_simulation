
#!/bin/bash

if [ -f ".buildpath" ]; then
    previous_path=$(cat .buildpath)

    if [ "$previous_path" != "$(pwd)" ]; then
        cd build
        shopt -s extglob
        find . ! -name 'CMakeLists.txt' -delete
        cd ..

        echo "$(pwd)" > .buildpath
    fi
else
    echo "$(pwd)" > .buildpath
fi

cd build
cmake .
cmake --build .
./planets
