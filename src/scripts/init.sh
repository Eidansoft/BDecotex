#!/bin/bash

function migrate(){
    python nnmm/manage.py makemigrations
    python nnmm/manage.py migrate
}

function start(){
    python nnmm/manage.py runserver 0.0.0.0:8000
}

function initialize(){
    python nnmm/manage.py createsuperuser
}

function install_devel_deps(){
    pip install ipdb
}

# Set the folder to project, no matter from where the script was called.
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd $SCRIPT_DIR/..

install_devel_deps
migrate
initialize
start
