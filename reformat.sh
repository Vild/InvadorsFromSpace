#!/bin/bash
find . -iname "*.cpp" -exec clang-format -i -style=file {} \;
find . -iname "*.hpp" -exec clang-format -i -style=file {} \;