#!/bin/bash

python brokerlib.py 127.0.0.1 5672 &
trap "kill $!" EXIT

sleep 0.2

./client amqp://127.0.0.1 q0 100
