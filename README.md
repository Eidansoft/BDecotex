# BDecotex
Personal solution for a small textil PYME management

## Description
This is a homemade solution for a small company in order to solve some data issues regarding the clothes models.

## Dependencies
In order to run the project you just need Git and Docker installed.

## Run
To run this project, all dependnecies are already configured at the docker image and container.
I just created a shellscript to make completely easy the deployment. Just execute from the command line (on win you can use the Git Bash):

### Create the Docker image with all dependencies
To create the docker image. This process will create the image to build the container in the next step; also here the image is configured with all necessary dependencies.

    ./run.sh create

### Initialize DB (only needed the very first time)
The first time you run the aplication (or if you have updated the source code and there is model changes) the DB needs to be created, for this you must create migrations and apply it all. To automatize this you can just run:

    ./run.sh initialize

### Start the server
To launch a docker container running the service at default configuration you just run:

    ./run.sh start

With this last command you will create a container and run the Django server. At the console you will see the listen port. Usually unless you have changed it, the web interface will be acessible from localhost:8000

## Configuration
You can easely access to a bash console into the running container executing:

    ./run.sh bash

From this console you can launch any Django command directly, for example to add a new super user:

    python /mnt/nnmm/manage.py createsuperuser

