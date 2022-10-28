# base image
FROM ubuntu
MAINTAINER Ratnesh
# copy app inside container app
COPY app /app
# WORKING DIR
WORKDIR /app
# execute hello inside container
RUN ["chmod", "755", "entry.sh"]
ENTRYPOINT ["./entry.sh"]
