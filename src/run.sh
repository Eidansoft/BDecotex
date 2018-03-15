#!/bin/bash
# author: eidansoft

function create(){
    cp requirements.txt docker-nnmm-prod/requirements.txt
    cp requirements.txt docker-nnmm-dev/requirements.txt
    docker build docker-nnmm-prod -t nnmm-prod
    docker build docker-nnmm-dev -t nnmm-dev
}

function run(){
    docker run -it -v $(pwd):/mnt --rm -p 8000:8000 --name nnmm nnmm-prod python /mnt/nnmm/manage.py runserver 0.0.0.0:8000
}

function devel(){
    docker run -it -v $(pwd):/mnt --rm -p 8000:8000 --name nnmm nnmm-dev /bin/bash
}

function __init__() {
    case "$1" in
        create)
            create
            ;;
        run)
            run
            ;;
        devel)
            devel
            ;;
        *)
            echo "Debes indicar: "
            echo "    - <create> para crear las imagenes del docker"
            echo "    - <run> para lanzar el servidor"
            echo "    - <devel> para lanzar el servidor en modo de desarrollo"
            echo ""
            ;;
     esac
}

# Set the folder to project, no matter from where the script was called.
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd $SCRIPT_DIR
__init__ $@
