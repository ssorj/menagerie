#!/bin/bash

python brokerlib.py 127.0.0.1 5672 &
pid=$!

sleep 1

./client amqp://127.0.0.1 q0 1

kill $pid
