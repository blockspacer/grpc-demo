FROM insready/bazel

EXPOSE 9090

RUN apt-get -y update &&\
    apt-get upgrade -y bazel

ADD . /code/grpc-demo

RUN rm /code/grpc-demo/server/include
RUN rm /code/grpc-demo/server/lib

COPY ./docker/server/include /code/grpc-demo/server/include
COPY ./docker/server/lib /code/grpc-demo/server/lib

WORKDIR /code/grpc-demo

# 把依赖库都安装了
RUN bazel build //server:server

# 运行时编译
CMD bazel run //server:server
