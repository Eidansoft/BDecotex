#!/bin/bash
# author: eidansoft

function create(){
    docker build . -t nnmm
}

function start(){
    docker run -it -v $(pwd):/mnt --rm -p 8000:8000 --name nnmm nnmm python /mnt/nnmm/manage.py runserver 0.0.0.0:8000
}

function initialize(){
    docker run -it -v $(pwd):/mnt --rm -p 8000:8000 --name nnmm nnmm /mnt/scripts/init_db.sh
}

function bash(){
    docker container exec -it nnmm /bin/bash
}

function __init__() {
    case "$1" in
        create)
            create
            ;;
        start)
            start
            ;;
        bash)
            bash
            ;;
        initialize)
            initialize
            ;;
        *)
            echo "Debes indicar: create o start."
            ;;
     esac
}

# Set the folder to project, no matter from where the script was called.
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd $SCRIPT_DIR
__init__ $@
