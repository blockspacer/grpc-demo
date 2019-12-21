FROM envoyproxy/envoy:latest

WORKDIR /etc/envoy

COPY ./envoy.yaml /etc/envoy/envoy.yaml

COPY ./scripts/gen_certs.sh /etc/envoy/gen_certs.sh

RUN sh gen_certs.sh

RUN ls

CMD /usr/local/bin/envoy -c /etc/envoy/envoy.yaml -l trace --log-path /tmp/envoy_info.log
