# Base image
FROM python:3

# author
LABEL maintainer=eidansoft

WORKDIR /mnt

COPY requirements.txt /mnt

RUN apt-get update && \
    apt-get install mdbtools -y && \
    pip install -r /mnt/requirements.txt

