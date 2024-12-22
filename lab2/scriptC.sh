#!/bin/bash

SERVER_URL="http://127.0.0.1/compute"

iteration=1  

while true; do
    sleep_interval=$((5 + RANDOM % 6))
    echo "Iteration $iteration: Waiting for $sleep_interval seconds..."
    sleep $sleep_interval

    echo "Iteration $iteration: Sending HTTP GET request to $SERVER_URL..."
    response=$(curl -i -X GET $SERVER_URL 2>&1)
    
    echo "Iteration $iteration: Server Response:"
    echo "$response"
    echo "---------------------------------------------------"

    iteration=$((iteration + 1))
done
