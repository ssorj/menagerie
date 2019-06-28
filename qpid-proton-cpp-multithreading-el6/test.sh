#!/bin/bash

set -ex

python brokerlib.py --host 127.0.0.1 --port 5672 &
trap "kill $!" EXIT

sleep 0.2

build/client amqp://127.0.0.1 q0 100
build/client-flow-control amqp://127.0.0.1 q0 100 10
