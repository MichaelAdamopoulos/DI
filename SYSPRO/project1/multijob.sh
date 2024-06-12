#!/bin/bash

# Check that we received at least one file
if [ $# -lt 1 ]; then
    echo "Usage: $0 <file1> <file2> ... <fileN>"
    exit 1
fi

# Iterate each readable file and run each non empty line
for file in "$@"; do
    if [ ! -f "$file" ] || [ ! -r "$file" ]; then 
        echo "File $file does not exist or is not readable"
        continue
    fi
    cat "$file" | while read -r line; do
        if [ -n "$line" ]; then
            ./jobCommander issueJob $line
        fi
    done
done
