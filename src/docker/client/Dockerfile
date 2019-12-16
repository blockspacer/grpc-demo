FROM grpcweb/common

WORKDIR /github/grpc-demo/src/protos

RUN protoc -I=. server.proto \
--js_out=import_style=commonjs:. \
--grpc-web_out=import_style=commonjs,mode=grpcwebtext:.

WORKDIR /github/grpc-demo/src/client/

RUN npm install

EXPOSE 8081
CMD ["npm", "run", "serve"]