#!/bin/bash

start_container() {
    local name=$1
    local cpu=$2
    if docker ps -a --filter "name=^${name}$" --format "{{.Names}}" | grep -wq "^${name}$"; then
        echo "$(date) - Container $name already exists. Removing..."
        docker rm -f "$name" || { echo "$(date) - Failed to remove container $name"; return 1; }
    fi
    echo "$(date) - Attempting to start container $name on CPU core #$cpu..."
    container_id=$(docker run --name "$name" --cpuset-cpus="$cpu" -d ilyamaluk/devops)
    if [ $? -eq 0 ]; then
        echo "$(date) - Server $name started | ID: $container_id"
    else
        echo "$(date) - Failed to start container $name"
    fi
}

is_container_busy() {
    local container=$1
    echo "$(date) - Checking if $container is busy..."
    local cpu_usage
    cpu_usage=$(docker stats --no-stream --format "{{.CPUPerc}}" "$container" | sed 's/%//')
    echo "$(date) - CPU usage for $container: $cpu_usage%"
    if (( $(echo "$cpu_usage > 20.0" | bc -l) )); then
        echo "$(date) - $container is busy."
        return 0
    else
        echo "$(date) - $container is idle."
        return 1
    fi
}

cleanup() {
    echo "$(date) - Script termination detected. Initiating cleanup..."
    for container in srv1 srv2 srv3; do
        if docker ps --filter "name=^${container}$" --format "{{.Names}}" | grep -wq "^${container}$"; then
            echo "$(date) - Stopping $container..."
            docker stop "$container" || echo "$(date) - Failed to stop $container"
            echo "$(date) - Removing $container..."
            docker rm "$container" || echo "$(date) - Failed to remove $container"
            echo "$(date) - $container stopped and removed."
        else
            echo "$(date) - $container is not running, skipping."
        fi
    done
    echo "$(date) - Cleanup complete. Exiting."
    exit 0
}

trap cleanup SIGINT SIGTERM

get_cpu_core() {
    case $1 in
        srv1) echo 0 ;;
        srv2) echo 1 ;;
        srv3) echo 2 ;;
        *) echo 0 ;;
    esac
}

start_container "srv1" 0

declare -A busy_count idle_count

while true; do
    echo "---------------------------------------------------"
    echo "$(date) - Starting a new monitoring cycle..."

    sleep 60
    containers=(srv1 srv2 srv3)

    for i in "${!containers[@]}"; do
        container=${containers[$i]}
        echo "$(date) - Checking server: $container"

        if docker ps --filter "name=^${container}$" --format "{{.Names}}" | grep -wq "^${container}$"; then
            if is_container_busy "$container"; then
                busy_count["$container"]=$(( ${busy_count["$container"]:-0} + 1 ))
                idle_count["$container"]=0
                if [ "${busy_count["$container"]}" -ge 2 ]; then
                    next_index=$((i + 1))
                    next_container=${containers[$next_index]}
                    if [ -n "$next_container" ]; then
                        echo "$(date) - $container has been busy for 2 consecutive checks. Checking if $next_container needs to be started..."
                        if ! docker ps --filter "name=^${next_container}$" --format "{{.Names}}" | grep -wq "^${next_container}$"; then
                            cpu_core=$(get_cpu_core "$next_container")
                            start_container "$next_container" "$cpu_core"
                        else
                            echo "$(date) - $next_container is already running."
                        fi
                    fi
                fi
            else
                busy_count["$container"]=0
                idle_count["$container"]=$(( ${idle_count["$container"]:-0} + 1 ))
                if [[ "$container" == "srv2" || "$container" == "srv3" ]]; then
                    if [ "${idle_count["$container"]}" -ge 2 ]; then
                        echo "$(date) - $container has been idle for 2 consecutive checks. Stopping..."
                        docker stop "$container" && docker rm "$container"
                        echo "$(date) - $container stopped and removed due to inactivity."
                        busy_count["$container"]=0
                        idle_count["$container"]=0
                    fi
                fi
            fi
        else
            echo "$(date) - $container is not running."
        fi
    done

    echo "$(date) - Checking for updates to ilyamaluk/devops..."
    pull_output=$(docker pull ilyamaluk/devops 2>&1)
    echo "$pull_output"
    if echo "$pull_output" | grep -q "Downloaded newer image"; then
        echo "$(date) - New image detected. Performing rolling updates..."
        for container in srv1 srv2 srv3; do
            if docker ps --filter "name=^${container}$" --format "{{.Names}}" | grep -wq "^${container}$"; then
                echo "$(date) - Updating $container..."
                docker stop "$container" && docker rm "$container"
                cpu_core=$(get_cpu_core "$container")
                start_container "$container" "$cpu_core"
                echo "$(date) - $container updated."
                sleep 5
            else
                echo "$(date) - $container is not running. Skipping update."
            fi
        done
    else
        echo "$(date) - No updates found."
    fi
done
