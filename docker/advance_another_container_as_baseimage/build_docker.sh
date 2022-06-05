#!/bin/bash

BASE_IMAGE=baseimage_2_0_0
#name should not overlap as it would create error in grep
TEMP_BASE_IMG_NAME=temp_base_img
FINAL_IMG_NAME=hello

echo "Temp img name: ${TEMP_BASE_IMG_NAME}"
echo "Final img name: ${FINAL_IMG_NAME}"

set -x 
echo "Deleting if image already present "
docker stop ${TEMP_BASE_IMG_NAME} ${FINAL_IMG_NAME}
docker rm ${TEMP_BASE_IMG_NAME} ${FINAL_IMG_NAME}
docker rmi ${TEMP_BASE_IMG_NAME} ${FINAL_IMG_NAME}
sleep 1

docker run -itd --privileged --name ${TEMP_BASE_IMG_NAME} --network host ${BASE_IMAGE} 
echo -e "copying all files to container \n "
docker exec -it ${TEMP_BASE_IMG_NAME} mkdir -p /dockerHome
docker exec -it ${TEMP_BASE_IMG_NAME} mkdir -p /learningDocker
docker exec -it ${TEMP_BASE_IMG_NAME} mkdir -p /home/testDir
docker cp app ${TEMP_BASE_IMG_NAME}:/dockerHome/
docker cp app ${TEMP_BASE_IMG_NAME}:/learningDocker/
set -x ##echo on
### get the image containerId, paste and run.
tempImageContainerId=`docker container ls | grep ${TEMP_BASE_IMG_NAME} | awk {'print $1'}`
docker commit ${tempImageContainerId} ${TEMP_BASE_IMG_NAME}


echo "Do you want to build the docker?"
echo "(Press y/Y to build or other to exit)"
read build_flag
if [ ${build_flag} == 'y' ] || [ ${build_flag} == 'Y' ];
then
	docker build -t ${FINAL_IMG_NAME} .
else
	echo "Docker was not build"
fi


echo "Do you want to run the docker?"
echo "(Press y/Y to run or other to exit)"
read run_flag
if [ ${run_flag} == 'y' ] || [ ${run_flag} == 'Y' ];
then
	nohup docker run -itd --privileged --restart always --log-opt max-size=100m --log-opt max-file=3 -v /etc/:/etc/ --name ${FINAL_IMG_NAME} --network host ${FINAL_IMG_NAME} &
	echo " docker run , executed, "
else
        echo "Docker did not run, ${FINAL_IMG_NAME}"
fi


sleep 1
echo "Do you want to save the docker?"
echo "(Press y/Y to save or other to exit)"
read save_flag
if [ ${save_flag} == 'y' ] || [ ${save_flag} == 'Y' ];
then
	finalImageContainerId=`docker container ls | grep ${FINAL_IMG_NAME} | awk {'print $1'}`
	docker commit ${finalImageContainerId} ${FINAL_IMG_NAME}:latest
	docker save -o ${FINAL_IMG_NAME}.tar ${FINAL_IMG_NAME}:latest

	docker stop ${TEMP_BASE_IMG_NAME} ${FINAL_IMG_NAME}
	docker rm ${TEMP_BASE_IMG_NAME} ${FINAL_IMG_NAME}
	docker rmi ${TEMP_BASE_IMG_NAME} ${FINAL_IMG_NAME}
	echo -e "docker creation completed, imageName: ${FINAL_IMG_NAME} ";
else
	echo -e "docker creation is not done ";
fi

set +x

#############################
#	END OF FILE
#############################
