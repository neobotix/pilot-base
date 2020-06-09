#!/bin/bash

cd $(dirname "$0")

vnxcppcodegen --cleanup generated/ pilot.sensors modules/ ../interface/ $1

