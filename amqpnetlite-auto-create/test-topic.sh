#!/bin/bash

dotnet build amqpnetlite/AutoCreate/TopicSend
dotnet build amqpnetlite/AutoCreate/TopicReceive

podman run -d --rm --name test-broker -p 5672:5672 -e AMQ_USER=admin -e AMQ_PASSWORD=admin quay.io/artemiscloud/activemq-artemis-broker

sleep 10

# The receiver must run first in order to see messages sent to a topic
dotnet run --project amqpnetlite/AutoCreate/TopicReceive amqp://localhost:5672 some-topic 1 &
pid=$!

dotnet run --project amqpnetlite/AutoCreate/TopicSend amqp://localhost:5672 some-topic abc123

kill $pid

podman kill test-broker
