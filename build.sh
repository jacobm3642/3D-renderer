#! /bin/bash
project_dirctory=$(pwd)
files=$(find $project_dirctory/src -not -path "$project_directory/src/test*" -name '*.c' -type f -printf "%p\n" | grep -v '/test/')  
uni_flags="-m64 -I./include/" 

while getopts ":rdt" opt; do
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
    \?)
      echo "Invalid option: -$OPTARG" >&2
      build_flags=""
      run_path=""
      ;;
  esac
done

gcc $build_flags
$run_path/main
