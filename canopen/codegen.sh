#!/bin/bash

cd $(dirname "$0")

vnxcppcodegen --cleanup generated/ pilot.base.canopen interface/ $1

