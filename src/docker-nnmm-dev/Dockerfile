# Base image
FROM nnmm-prod

# author
LABEL maintainer=eidansoft

WORKDIR /mnt

COPY requirements.txt /mnt
COPY requirements-dev.txt /mnt
COPY commands.sh /usr/local/bin/

RUN echo "echo 'Run <M>igrations:'" >> /root/.bashrc && \
    echo "echo '    - python nnmm/manage.py makemigrations'" >> /root/.bashrc && \
    echo "echo '    - python nnmm/manage.py migrate'" >> /root/.bashrc && \
    echo "echo '<S>tart server:'" >> /root/.bashrc && \
    echo "echo '    - python nnmm/manage.py runserver 0.0.0.0:8000'" >> /root/.bashrc && \
    echo "echo '<C>reate superuser <createuser>:'" >> /root/.bashrc && \
    echo "echo '    - python nnmm/manage.py createsuperuser'" >> /root/.bashrc && \
    echo "echo ''" >> /root/.bashrc && \
    echo "echo 'All this can be executed with the letter assigned to the command (the one between the tags <>)'" >> /root/.bashrc && \
    echo "alias M='commands.sh migrate'" >> /root/.bashrc && \
    echo "alias S='commands.sh start'" >> /root/.bashrc && \
    echo "alias C='commands.sh createuser'" >> /root/.bashrc

RUN apt-get update && \
    apt-get install mdbtools -y && \
    pip install -r /mnt/requirements-dev.txt

