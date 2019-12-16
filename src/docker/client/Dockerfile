FROM grpcweb/common

WORKDIR /github/grpc-demo/src/protos

RUN protoc -I=. server.proto \
--js_out=import_style=commonjs:./commonjs-example \
--grpc-web_out=import_style=commonjs,mode=grpcwebtext:./commonjs-example

WORKDIR /github/grpc-demo/src/client/

RUN npm install && \
  npm run serve

EXPOSE 8081
