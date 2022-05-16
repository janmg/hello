# hello
Loadbalanced Hello World Webservers in many programming languages

# Components
- haproxy for loadbalancing
- go lang
- nodejs
- java (on jetty)
- c++
- perl
- python
- rust (to come)

# AWS
Can be run as docker in AWS using ECR

http://docs.aws.amazon.com/AmazonECR/latest/userguide/ECR_AWSCLI.html

http://docs.aws.amazon.com/AmazonECR/latest/userguide/ECR_GetStarted.html

https://eu-central-1.console.aws.amazon.com/ec2/v2/home?region=eu-central-1#Instances:sort=dnsName

https://eu-central-1.console.aws.amazon.com/ecs/home?region=eu-central-1#/repositories

https://nodejs.org/en/docs/guides/nodejs-docker-webapp/

ssh ec2-user@ec2-35-157-169-248.eu-central-1.compute.amazonaws.com -i .ssh/amazon.pem 

https://aws.amazon.com/cli/

# Clone default Alpine docker images
git clone https://github.com/docker-library/haproxy.git

git clone https://github.com/docker-library/golang.git

sh -c "$(aws ecr get-login)"


docker build -t 138546162266.dkr.ecr.eu-central-1.amazonaws.com/haproxy-base haproxy/1.7/alpine

docker push 138546162266.dkr.ecr.eu-central-1.amazonaws.com/haproxy-base

docker build -t 138546162266.dkr.ecr.eu-central-1.amazonaws.com/haproxy my-haproxy

docker push 138546162266.dkr.ecr.eu-central-1.amazonaws.com/haproxy:latest



docker build -t 138546162266.dkr.ecr.eu-central-1.amazonaws.com/golang-base golang/1.8/alpine/

docker push 138546162266.dkr.ecr.eu-central-1.amazonaws.com/golang-base:latest

docker build -t 138546162266.dkr.ecr.eu-central-1.amazonaws.com/golang my-golang

docker push 138546162266.dkr.ecr.eu-central-1.amazonaws.com/golang:latest


docker build -t 138546162266.dkr.ecr.eu-central-1.amazonaws.com/nodejs my-nodejs

docker push 138546162266.dkr.ecr.eu-central-1.amazonaws.com/nodejs:latest

# Troubleshoot
docker run -ti 138546162266.dkr.ecr.eu-central-1.amazonaws.com/haproxy:latest /bin/sh

# RUN manually
docker run -d -p 80:80/tcp --restart=always --name=haproxy 138546162266.dkr.ecr.eu-central-1.amazonaws.com/haproxy:latest

docker run -d -p 8001:8001/tcp --restart=always --name=golang 138546162266.dkr.ecr.eu-central-1.amazonaws.com/golang:latest

docker run -d -p 8002:8002/tcp --restart=always --name=nodejs 138546162266.dkr.ecr.eu-central-1.amazonaws.com/nodejs:latest

# Service Discovery
http://jasonwilder.com/blog/2014/07/15/docker-service-discovery/

# Clean up
for DOCK in "haproxy" "golang" "nodejs";do docker stop ${DOCK};docker rm ${DOCK};done

aws ecr batch-delete-image --repository-name ubuntu --image-ids imageTag=trusty

aws ecr delete-repository --repository-name ubuntu --force
