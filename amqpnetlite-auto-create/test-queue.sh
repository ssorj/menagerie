#!/bin/bash

dotnet build amqpnetlite/AutoCreate/QueueSend
dotnet build amqpnetlite/AutoCreate/QueueReceive

podman run -d --rm --name test-broker -p 5672:5672 -e AMQ_USER=admin -e AMQ_PASSWORD=admin quay.io/artemiscloud/activemq-artemis-broker

sleep 10

dotnet run --project amqpnetlite/AutoCreate/QueueSend amqp://localhost:5672 some-queue abc123
dotnet run --project amqpnetlite/AutoCreate/QueueReceive amqp://localhost:5672 some-queue 1

podman kill test-broker
