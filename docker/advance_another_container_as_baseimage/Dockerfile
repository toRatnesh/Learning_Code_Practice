# temp_base_img will act as base image it will be built inside build_docker.sh
FROM temp_base_img
MAINTAINER Ratnesh
# WORKING DIR
WORKDIR /dockerHome
# execute hello inside container
RUN ["chmod", "755", "entry.sh"]
ENTRYPOINT ["./entry.sh"]
