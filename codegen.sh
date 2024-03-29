#!/bin/bash

VNX_INTERFACE_DIR=${VNX_INTERFACE_DIR:-/usr/interface}

VNX_INCLUDE=$1

if [ -z "$VNX_INCLUDE" ]; then
	VNX_INCLUDE=${VNX_INTERFACE_DIR}/vnx/
fi

cd $(dirname "$0")
DIR="$(pwd)"

./canopen/codegen.sh "${DIR}/interface/ $VNX_INCLUDE"

vnxcppcodegen --cleanup generated/ pilot.base interface/ modules/ $VNX_INCLUDE

