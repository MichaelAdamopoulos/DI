#!/bin/bash

# Function to stop jobs from a list
allJobsStop() {
    # Iterate each line, clean the input to get the job and stop it
    echo "$1" | while read -r job; do
        job_ID=$(echo "$job" | cut -d',' -f1 | tr -d '<')
        if [ -n "$job_ID" ]; then
            jobCommander stop "$job_ID"
        fi
    done
}

# Get a list of queued and running jobs 
# Stop all jobs, but first the queued so no queued job can become running

queued=$(jobCommander poll queued)

if [ -n "$queued" ]; then
    allJobsStop "$queued"
fi

running=$(jobCommander poll running)

if [ -n "$running" ]; then
    allJobsStop "$running"
fi
