#!/usr/bin/env bash

set -o pipefail

function print_header() {
  echo -e "\n***** ${1} *****"
}

function check_log() {
  LOG=$({ ${1}; } 2>&1)
  STATUS=$?
  echo "$LOG"
  if echo "$LOG" | grep -q -E "${2}"; then
    exit 1
  fi

  if [ $STATUS -ne 0 ]; then
    exit $STATUS
  fi
}

if [ $# != 2 ]; then
  echo "Invalid number of parameters"
  exit 0
fi

if [ "$1" = "--cpplint" ] || [ "$1" = "--all" ]; then
  print_header "RUN cpplint"
  check_log "cpplint $2" "Can't open for reading"
fi

if [ "$1" = "--cppcheck" ] || [ "$1" = "--all" ]; then
  print_header "RUN cppcheck"
  check_log "cppcheck $2 --enable=all --inconclusive --error-exitcode=1 --suppress=missingIncludeSystem --suppress=unusedFunction" "cppcheck failed"
fi
print_header "SUCCESS"