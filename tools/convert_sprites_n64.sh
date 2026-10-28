#!/bin/bash
# Convert C-Dogs graphics PNGs into compressed Libdragon sprites (RGBA16)
set -e

TOOLCHAIN="${N64_INST:-/Users/gcoursaget/libdragon-toolchain}"
MKSPRITE="$TOOLCHAIN/bin/mksprite"

if [ ! -f "$MKSPRITE" ]; then
    echo "Error: mksprite not found at $MKSPRITE"
    exit 1
fi

SRC_DIR="graphics"
OUT_DIR="filesystem/graphics"

echo "=== Converting sprites from $SRC_DIR to $OUT_DIR (Format: RGBA16, Compression: level 1) ==="
mkdir -p "$OUT_DIR"

# Find all PNG files except editor and source blend files
find "$SRC_DIR" -type f -name "*.png" ! -path "*/editor/*" | while read -r png_file; do
    rel_path="${png_file#$SRC_DIR/}"
    rel_dir=$(dirname "$rel_path")
    target_dir="$OUT_DIR/$rel_dir"
    mkdir -p "$target_dir"
    "$MKSPRITE" --format RGBA16 -c 1 -o "$target_dir" "$png_file"
done

# Also copy metadata text and json files (e.g. font.json, frame sizes .txt)
find "$SRC_DIR" -type f \( -name "*.txt" -o -name "*.json" \) ! -path "*/editor/*" | while read -r meta_file; do
    rel_path="${meta_file#$SRC_DIR/}"
    target_file="$OUT_DIR/$rel_path"
    mkdir -p "$(dirname "$target_file")"
    cp "$meta_file" "$target_file"
done

echo "=== Sprite conversion complete! ==="
