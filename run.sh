#!/usr/bin/env bash

if [ -d "docker/db/empty" ]; then
  rm -rf ./docker/db/empty
fi

docker-compose up