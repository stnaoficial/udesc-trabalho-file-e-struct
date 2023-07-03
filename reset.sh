#!/bin/bash

# Set the filename
filename='database.bin'

# Check the file is exists or not
if [ -f $filename ]; then
    rm $filename
    echo "$filename is removed"

# Create an empty file
else
    touch $filename
    echo "$filename was created"
fi