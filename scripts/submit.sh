#!/bin/bash

curl -F 'myFile=@'"$1" -F "myName=erooney" http://samurai.phys.gwu.edu:8080/upload
