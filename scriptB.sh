#!/bin/bash

SERVER_URL="http://127.0.0.1/compute"
iteration=1

while true; do
    sleep_interval=$((5 + RANDOM % 6))
    echo "$(date) - Iteration $iteration: Sending HTTP GET request to $SERVER_URL..."
    curl -s -o /dev/null -X GET "$SERVER_URL" &
    iteration=$((iteration + 1))
	echo "---------------------------------------------------"
    echo "$(date) - Iteration $iteration: Waiting for $sleep_interval seconds..."
    sleep "$sleep_interval"
done
