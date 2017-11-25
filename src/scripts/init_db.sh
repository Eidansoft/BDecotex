#!/bin/bash

function __init__(){
    python nnmm/manage.py makemigrations
    python nnmm/manage.py migrate
}

# Set the folder to project, no matter from where the script was called.
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd $SCRIPT_DIR/..
__init__
