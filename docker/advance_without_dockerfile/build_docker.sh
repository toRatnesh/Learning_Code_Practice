#!/bin/bash

#################################
#	This example demonstrates about creation of a docker image without Dockerfile
#	
#	This example 
#		runs a container using base image
#		makes required changes inside container
#		build image using 'docker commit' 
#		save image using 'docker save'
#
#################################


BASE_IMAGE=baseimage_2_0_0
TEMP_IMG_NAME=hello_temp
FINAL_IMG_NAME=hello

echo "Final img name: ${TEMP_IMG_NAME}"

set -x 
echo "Deleting if image already present "
docker stop ${TEMP_IMG_NAME} 
docker rm ${TEMP_IMG_NAME}
docker rmi ${FINAL_IMG_NAME}:version-1
sleep 1

docker run -itd --privileged --name ${TEMP_IMG_NAME} --network host ${BASE_IMAGE} 
echo -e "copying all files to container \n "
docker exec -it ${TEMP_IMG_NAME} mkdir -p /dockerHome
docker exec -it ${TEMP_IMG_NAME} mkdir -p /learningDocker
docker exec -it ${TEMP_IMG_NAME} mkdir -p /home/testDir
docker cp app ${TEMP_IMG_NAME}:/dockerHome/
docker cp app ${TEMP_IMG_NAME}:/learningDocker/
set -x ##echo on
sleep 1

echo "Do you want to save the docker?"
echo "(Press y/Y to save or other to exit)"
read save_flag
if [ ${save_flag} == 'y' ] || [ ${save_flag} == 'Y' ];
then
	tempImageContainerId=`docker container ls | grep ${TEMP_IMG_NAME} | awk {'print $1'}`
	docker commit -c "WORKDIR /dockerHome" ${tempImageContainerId} ${FINAL_IMG_NAME}:version-1
	docker save -o ${FINAL_IMG_NAME}.tar ${FINAL_IMG_NAME}:version-1
	
	docker stop ${TEMP_IMG_NAME}
	docker rm ${TEMP_IMG_NAME}
	docker rmi ${FINAL_IMG_NAME}:version-1
	echo -e "docker creation completed, imageName: ${FINAL_IMG_NAME} ";
else
	echo -e "docker creation is not done ";
fi

set +x

#############################
#	END OF FILE
#############################
