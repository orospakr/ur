#!/bin/sh

echo "Building protos..."

set -e
set -x

# Dump C++ generated proto code in src/proto:
protoc -I=. --cpp_out=src proto/agm.proto

protoc -I=. --swift_out=builder/UR\ Builder/ proto/agm.proto
