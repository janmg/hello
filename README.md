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
- lua
- c#

# AWS

Deploy to AWS using ECR and ECS:

```bash
# Authenticate with ECR
aws ecr get-login-password --region eu-central-1 | docker login --username AWS --password-stdin 138546162266.dkr.ecr.eu-central-1.amazonaws.com

# Build and push
docker build -t 138546162266.dkr.ecr.eu-central-1.amazonaws.com/haproxy haproxy/
docker push 138546162266.dkr.ecr.eu-central-1.amazonaws.com/haproxy

docker build -t 138546162266.dkr.ecr.eu-central-1.amazonaws.com/golang web/golang/
docker push 138546162266.dkr.ecr.eu-central-1.amazonaws.com/golang

docker build -t 138546162266.dkr.ecr.eu-central-1.amazonaws.com/nodejs web/nodejs/
docker push 138546162266.dkr.ecr.eu-central-1.amazonaws.com/nodejs
```

Console links:
- EC2: https://eu-central-1.console.aws.amazon.com/ec2/v2/home
- ECS: https://eu-central-1.console.aws.amazon.com/ecs/home

## Local Build & Run

Build images locally with `alpine:edge` base:

```bash
# Build all web servers
docker build -t haproxy haproxy/
docker build -t golang web/golang/
docker build -t nodejs web/nodejs/
docker build -t java web/jetty/
docker build -t csharp web/csharp/
docker build -t python web/python/
docker build -t flask web/flask/
docker build -t perl web/perl/
docker build -t rust web/rust/
docker build -t lua web/lua/
docker build -t c web/c/
docker build -t cpp 'web/c++/'
```

Run containers locally:

```bash
# Start backends
docker run -d --name golang -p 8001:8080 golang
docker run -d --name nodejs -p 8002:8080 nodejs
docker run -d --name java -p 8003:8080 java
docker run -d --name python -p 8004:8080 python
docker run -d --name flask -p 8005:8080 flask
docker run -d --name perl -p 8006:8080 perl
docker run -d --name rust -p 8007:8080 rust
docker run -d --name lua -p 8008:8080 lua
docker run -d --name csharp -p 8009:8080 csharp
docker run -d --name c -p 8010:8080 c
docker run -d --name cpp -p 8011:8080 cpp

# Start HAProxy load balancer
docker run -d --name haproxy -p 80:80 haproxy
```

Clean up:

```bash
docker stop golang nodejs java python flask perl rust lua csharp c cpp haproxy
docker rm golang nodejs java python flask perl rust lua csharp c cpp haproxy
```
