#! /bin/bash
project_dirctory=$(pwd)
files=$(find $project_dirctory/src -not -path "$project_directory/src/test*" -name '*.c' -type f -printf "%p\n" | grep -v '/test/')  
uni_flags="-m64 -I./include/ -lm -lSDL2 -lGL -lGLEW -Wno-error=implicit-fallthrough -Wno-implicit-fallthrough" 
valgrind="F"

echo -e "\033[31mWARINING UNSTABLE ON WAYLAND\033[0m"

if [ ! -d ./build ]; then
    mkdir build
fi

if [ ! -d ./build/debug ]; then
    mkdir build/debug
fi

if [ ! -d ./build/realise ]; then
    mkdir build/realise
fi

if [ ! -d ./build/testing ]; then
    mkdir build/testing
fi

while getopts ":rdtv" opt; do
  case $opt in
    t)
      echo "building tests ....." >&2 
      files=$(find $project_dirctory/src -name '*.c' -type f -printf "%p\n") 
      build_flags="$files -D test -g -lcheck -o ./build/testing/main $uni_flags"
      run_path=./build/testing
      ;;
    r)
      echo "Building Realise ....." >&2
      build_flags="$files -O3 -s -o ./build/realise/main $uni_flags"
      run_path=./build/realise
      ;;
    d)
      echo "Building Debug ....." >&2
      build_flags="$files -g -Wextra -Wall -Werror -o ./build/debug/main $uni_flags"
      run_path=./build/debug
      bear -- gcc $build_flags
      ;;
    v)
      valgrind="T"
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      build_flags=""
      run_path=""
      ;;
  esac
done

gcc $build_flags
$run_path/main

if [[ $valgrind == "T" ]]; then
  valgrind --leak-check=full --show-leak-kinds=all --log-file="valgrind.output.txt" ./build/debug/main
fi
