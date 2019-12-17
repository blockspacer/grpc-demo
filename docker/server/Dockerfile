FROM insready/bazel

RUN apt-get -y update && apt-get upgrade -y bazel

ADD . /code/grpc-demo

WORKDIR /code/grpc-demo

RUN bazel build //server:server

EXPOSE 9090

CMD ./bazel-bin/server/server
