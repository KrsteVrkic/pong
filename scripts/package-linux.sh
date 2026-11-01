#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build/release-linux-x86_64"
PACKAGE_DIR="$ROOT_DIR/dist/pong-linux-x86_64"
ARCHIVE="$ROOT_DIR/dist/pong-linux-x86_64.tar.gz"

cmake -S "$ROOT_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR" --parallel

rm -rf "$PACKAGE_DIR"
mkdir -p "$PACKAGE_DIR/assets/audio"
install -m 755 "$BUILD_DIR/pong" "$PACKAGE_DIR/pong"
install -m 644 "$ROOT_DIR"/assets/audio/*.wav "$PACKAGE_DIR/assets/audio/"

mkdir -p "$ROOT_DIR/dist"
tar -czf "$ARCHIVE" -C "$ROOT_DIR/dist" pong-linux-x86_64
printf 'Created %s\n' "$ARCHIVE"
