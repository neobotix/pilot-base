#!/bin/bash

VNX_INTERFACE_DIR=${VNX_INTERFACE_DIR:-/usr/interface}

cd $(dirname "$0")

vnxcppcodegen --cleanup generated/ pilot.base interface/ modules/ ${VNX_INTERFACE_DIR}/vnx/

