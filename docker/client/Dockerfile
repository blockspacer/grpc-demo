FROM grpcweb/common

EXPOSE 8081

WORKDIR /code/grpc-demo/protos

CMD protoc -I=. server.proto \
--js_out=import_style=commonjs:. \
--grpc-web_out=import_style=commonjs,mode=grpcwebtext:.

WORKDIR /code/grpc-demo/client/

CMD npm install && npm run serve