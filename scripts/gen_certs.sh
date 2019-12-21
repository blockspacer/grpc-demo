#!/bin/bash

openssl req -nodes -x509 -newkey rsa:4096 -keyout Envoy.key -out EnvoyCert.crt -days 365 -subj "/C=US/ST=CA/L=SF/O=Turbine Labs/OU=Envoy Division/CN=localhost"