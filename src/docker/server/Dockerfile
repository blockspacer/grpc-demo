FROM insready/bazel

RUN apt-get -y update && apt-get upgrade -y bazel

WORKDIR /github/grpc-demo

RUN git clone https://github.com/Calvin-cn/grpc-demo.git .

RUN bazel build //src/server:server

EXPOSE 9090
CMD ["./bazel-bin/src/server/server"]
