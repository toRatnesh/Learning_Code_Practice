ratnesh$ ll
total 8
drwxrwxr-x 5 root root 4096 May  9 16:38 app
-rw-r--r-- 1 root root  164 May  9 17:19 Dockerfile
ratnesh$
ratnesh$ pwd
/root/ratnesh/docker
ratnesh$ ll
total 8
drwxrwxr-x 5 root root 4096 May  9 16:38 app
-rw-r--r-- 1 root root  164 May  9 17:19 Dockerfile
ratnesh$ sudo docker build -t hello .
Sending build context to Docker daemon  949.8kB
Step 1/5 : FROM baseimage_2_0_0
 ---> 72c0b32ee42b
Step 2/5 : MAINTAINER Ratnesh
 ---> Running in 47ba918a6c60
Removing intermediate container 47ba918a6c60
 ---> 80ac2fc70615
Step 3/5 : COPY app /app
 ---> 5801cb7fd009
Step 4/5 : WORKDIR /app
 ---> Running in 26e46e2dcdb9
Removing intermediate container 26e46e2dcdb9
 ---> 8e39ce7bb691
Step 5/5 : CMD ["bin/hello"]
 ---> Running in dc1421c8992d
Removing intermediate container dc1421c8992d
 ---> de9a3b53e017
Successfully built de9a3b53e017
Successfully tagged hello:latest
ratnesh$ sudo docker images
REPOSITORY              TAG                 IMAGE ID            CREATED             SIZE
hello                   latest              de9a3b53e017        9 seconds ago       1.96GB
iothssps_v_6_4_0        latest              99efbf364aeb        3 months ago        2.25GB
jiohss_ps_baseimage     latest              890031959ebe        3 months ago        2.25GB
iothssps_v_6_3_2        latest              29c136881a90        10 months ago       2.08GB
hssps_v_6.3.3           latest              7d22da807481        10 months ago       2.08GB
hsscm_v_6.3.2           latest              66f6eedbaac2        10 months ago       2.08GB
aerospike_v_5_6_0_5-1   latest              30357d23cbab        10 months ago       2.01GB
aerospike_v_5_4_0_4-1   latest              579b80b74b3f        15 months ago       2.01GB
baseimage_2_0_0         latest              72c0b32ee42b        19 months ago       1.96GB
ratnesh$ sudo docker run -itd -v /home/ratnesh1.tiwari/docker/:/docker/ratnesh1.tiwari/ --name hello --network host hello &
[1] 61650
ratnesh$ 5135052b6c9dbb4937b30d183325bf6a05ef27c125226bf048135dfdfd391ace

[1]+  Done                    sudo docker run -itd -v /home/ratnesh1.tiwari/docker/:/docker/ratnesh1.tiwari/ --name hello --network host hello
ratnesh$ sudo docker ps
CONTAINER ID        IMAGE                   COMMAND             CREATED             STATUS              PORTS               NAMES
5135052b6c9d        hello                   "bin/hello"         12 seconds ago      Up 11 seconds                           hello
f977de635c01        baseimage_2_0_0         "/bin/bash"         3 months ago        Up 3 months                             jiohss_ps_baseimage
92001996752b        aerospike_v_5_6_0_5-1   "./entrypoint.sh"   10 months ago       Up 6 months                             hssdb1
93c3ab06e980        aerospike_v_5_4_0_4-1   "./entrypoint.sh"   15 months ago       Up 2 months                             aerodb
ratnesh$ sudo docker exec -it hello /bin/bash
[root@ps1 app]# pwd
/app
[root@ps1 app]# ll
total 20
drwxrwxr-x 2 root root 4096 May  8 18:22 bin
drwxrwxr-x 2 root root 4096 May  8 15:21 lib
-rw-rw-r-- 1 root root  260 May  8 17:56 Makefile
-rw-rw-r-- 1 root root  254 May  8 18:06 Makefile_hello
drwxrwxr-x 2 root root 4096 May  8 18:22 src
[root@ps1 app]# ls -l /docker/ratnesh1.tiwari/
total 8
drwxrwxr-x 5 1006 1006 4096 May  9 11:08 app
-rw-r--r-- 1 1006 1006  164 May  9 11:49 Dockerfile
[root@ps1 app]# ls -l ../
total 112
-rw-r--r--   1 root root 24938 Jul 16  2020 1
drwxr-xr-x   5 root root  4096 Jun  4 10:50 app
lrwxrwxrwx   1 root root     7 Jul 13  2020 bin -> usr/bin
dr-xr-xr-x   2 root root  4096 Dec 14  2017 boot
drwxr-xr-x   5 root root   360 Jun  4 10:50 dev
drwxr-xr-x   3 root root  4096 Jun  4 10:50 docker
drwxr-xr-x   1 root root  4096 Jun  4 10:50 etc
drwxr-xr-x   2 root root  4096 Jul 13  2020 home
lrwxrwxrwx   1 root root     7 Jul 13  2020 lib -> usr/lib
lrwxrwxrwx   1 root root     9 Jul 13  2020 lib64 -> usr/lib64
-rwxr-xr-x   1 root root 24938 Jul 16  2020 linux_ba.sh
drwxr-xr-x   2 root root  4096 Dec 14  2017 media
drwxr-xr-x   2 root root  4096 Dec 14  2017 mnt
drwxr-xr-x   1 root root  4096 Aug  5  2020 opt
dr-xr-xr-x 396 root root     0 Jun  4 10:50 proc
dr-xr-x---   1 root root  4096 Jul 16  2020 root
drwxr-xr-x   1 root root  4096 Oct 20  2020 run
lrwxrwxrwx   1 root root     8 Jul 13  2020 sbin -> usr/sbin
drwxr-xr-x   2 root root  4096 Dec 14  2017 srv
dr-xr-xr-x  13 root root     0 Aug  5  2021 sys
drwxrwxrwt   1 root root  4096 Oct 20  2020 tmp
drwxr-xr-x   1 root root  4096 Jul 13  2020 usr
drwxr-xr-x   1 root root  4096 Jul 13  2020 var
[root@ps1 app]# ps -ef
UID        PID  PPID  C STIME TTY          TIME CMD
root         1     0  0 10:50 pts/0    00:00:00 bin/hello
root         6     0  0 10:51 pts/1    00:00:00 /bin/bash
root        26     6  0 10:52 pts/1    00:00:00 ps -ef
[root@ps1 app]# exit
exit
ratnesh$ sudo docker ps
CONTAINER ID        IMAGE                   COMMAND             CREATED              STATUS              PORTS               NAMES
5135052b6c9d        hello                   "bin/hello"         About a minute ago   Up About a minute                       hello
f977de635c01        baseimage_2_0_0         "/bin/bash"         3 months ago         Up 3 months                             jiohss_ps_baseimage
92001996752b        aerospike_v_5_6_0_5-1   "./entrypoint.sh"   10 months ago        Up 6 months                             hssdb1
93c3ab06e980        aerospike_v_5_4_0_4-1   "./entrypoint.sh"   15 months ago        Up 2 months                             aerodb
ratnesh$ sudo docker stop hello
hello
ratnesh$ sudo docker ps
CONTAINER ID        IMAGE                   COMMAND             CREATED             STATUS              PORTS               NAMES
f977de635c01        baseimage_2_0_0         "/bin/bash"         3 months ago        Up 3 months                             jiohss_ps_baseimage
92001996752b        aerospike_v_5_6_0_5-1   "./entrypoint.sh"   10 months ago       Up 6 months                             hssdb1
93c3ab06e980        aerospike_v_5_4_0_4-1   "./entrypoint.sh"   15 months ago       Up 2 months                             aerodb
ratnesh$ sudo docker ps -a
CONTAINER ID        IMAGE                   COMMAND             CREATED             STATUS                        PORTS               NAMES
5135052b6c9d        hello                   "bin/hello"         2 minutes ago       Exited (137) 17 seconds ago                       hello
f977de635c01        baseimage_2_0_0         "/bin/bash"         3 months ago        Up 3 months                                       jiohss_ps_baseimage
24b3b1dc766c        be665879df27            "./entrypoint.sh"   10 months ago       Exited (137) 6 months ago                         hssps_v_6.3.3
92001996752b        aerospike_v_5_6_0_5-1   "./entrypoint.sh"   10 months ago       Up 6 months                                       hssdb1
93c3ab06e980        aerospike_v_5_4_0_4-1   "./entrypoint.sh"   15 months ago       Up 2 months                                       aerodb
ratnesh$ sudo docker rm hello
hello
ratnesh$ sudo docker ps -a
CONTAINER ID        IMAGE                   COMMAND             CREATED             STATUS                      PORTS               NAMES
f977de635c01        baseimage_2_0_0         "/bin/bash"         3 months ago        Up 3 months                                     jiohss_ps_baseimage
24b3b1dc766c        be665879df27            "./entrypoint.sh"   10 months ago       Exited (137) 6 months ago                       hssps_v_6.3.3
92001996752b        aerospike_v_5_6_0_5-1   "./entrypoint.sh"   10 months ago       Up 6 months                                     hssdb1
93c3ab06e980        aerospike_v_5_4_0_4-1   "./entrypoint.sh"   15 months ago       Up 2 months                                     aerodb
ratnesh$ sudo docker images
REPOSITORY              TAG                 IMAGE ID            CREATED             SIZE
hello                   latest              de9a3b53e017        3 minutes ago       1.96GB
iothssps_v_6_4_0        latest              99efbf364aeb        3 months ago        2.25GB
jiohss_ps_baseimage     latest              890031959ebe        3 months ago        2.25GB
iothssps_v_6_3_2        latest              29c136881a90        10 months ago       2.08GB
hssps_v_6.3.3           latest              7d22da807481        10 months ago       2.08GB
hsscm_v_6.3.2           latest              66f6eedbaac2        10 months ago       2.08GB
aerospike_v_5_6_0_5-1   latest              30357d23cbab        10 months ago       2.01GB
aerospike_v_5_4_0_4-1   latest              579b80b74b3f        15 months ago       2.01GB
baseimage_2_0_0         latest              72c0b32ee42b        19 months ago       1.96GB
ratnesh$ sudo docker rmi hello
Untagged: hello:latest
Deleted: sha256:de9a3b53e017453852a0bebe0519e385ea2b089c9c78fa2a52a1c7b87add6b7a
Deleted: sha256:8e39ce7bb691f494b401248cec17792ce20e3146994b1fe36af3333eb969b5a6
Deleted: sha256:5801cb7fd009174cc449ff1e269e79dc434078c0b3125a543921edb48f32d0de
Deleted: sha256:6ed2cd1ba318585251ed5594154a38d42e2905b0a37bb0006e319092205958ff
Deleted: sha256:80ac2fc70615e71db93397a6a902a3c3d23b2df4ac990e7c9a42c8de8ede40d7
ratnesh$ sudo docker images
REPOSITORY              TAG                 IMAGE ID            CREATED             SIZE
iothssps_v_6_4_0        latest              99efbf364aeb        3 months ago        2.25GB
jiohss_ps_baseimage     latest              890031959ebe        3 months ago        2.25GB
iothssps_v_6_3_2        latest              29c136881a90        10 months ago       2.08GB
hssps_v_6.3.3           latest              7d22da807481        10 months ago       2.08GB
hsscm_v_6.3.2           latest              66f6eedbaac2        10 months ago       2.08GB
aerospike_v_5_6_0_5-1   latest              30357d23cbab        10 months ago       2.01GB
aerospike_v_5_4_0_4-1   latest              579b80b74b3f        15 months ago       2.01GB
baseimage_2_0_0         latest              72c0b32ee42b        19 months ago       1.96GB
ratnesh$
ratnesh$
