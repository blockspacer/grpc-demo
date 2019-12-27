FROM insready/bazel

EXPOSE 9090

RUN apt-get -y update &&\
    apt-get upgrade -y bazel

ADD . /code/grpc-demo

WORKDIR /code/grpc-demo

# 把依赖库都安装了
RUN bazel build //server:server --define os=linux

# 运行时编译
CMD bazel run //server:server --define os=linux
