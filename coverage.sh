#!/bin/sh
set -euxo pipefail

# note: must have gcov and lcov installed

lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/Library/*' '/usr/*' '*/test/*' '*/googletest/*' --output-file coverage.info
lcov --list coverage.info
