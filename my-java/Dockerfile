FROM 138546162266.dkr.ecr.eu-central-1.amazonaws.com/java-base

#WORKDIR /usr/src/app/

COPY *.java / 
RUN javac *.java 

EXPOSE 8003
CMD [ "java", "NioHelloServer" ]
