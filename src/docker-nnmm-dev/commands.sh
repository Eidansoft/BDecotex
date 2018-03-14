#!/bin/bash

case "$1" in
    migrate)
        python nnmm/manage.py makemigrations
        python nnmm/manage.py migrate
        ;;
    start)
        python nnmm/manage.py runserver 0.0.0.0:8000
        ;;
    createuser)
        python nnmm/manage.py createsuperuser
        ;;
    *)
        echo "Error, el parametro <$1> no es valido."
        exit 1
        ;;
esac

exit 0
              

