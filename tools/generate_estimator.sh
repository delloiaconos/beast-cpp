#!/usr/bin/env bash

# SPDX-License-Identifier: GPL-3.0-only
#
# BEAST - Battery Estimation Architecture and Simulation Toolkit
#
# Generate the source and header files for a new Estimator from M4 templates.
#
# Usage:
#
#   NAME=UKF tools/generate_estimator.sh
#
# Optional variables:
#
#   FORCE=1
#   BEAST_AUTHOR="Author Name"
#   BEAST_REPOSITORY="https://github.com/user/beast-cpp.git"
#   BEAST_YEAR=2026
#   M4=m4
#
# Example:
#
#   NAME=UKF \
#   BEAST_AUTHOR="Salvatore Dello Iacono" \
#   tools/generate_estimator.sh
#

set -euo pipefail


# -----------------------------------------------------------------------------
# Utility functions
# -----------------------------------------------------------------------------

usage()
{
    cat <<EOF
Usage:
    NAME=<model-name> $(basename "$0")

Example:
    NAME=UKF $(basename "$0")

Optional environment variables:
    FORCE=1                 Overwrite existing generated files
    BEAST_AUTHOR=<name>     Author name
    BEAST_REPOSITORY=<url>  Project repository URL
    BEAST_YEAR=<year>       Copyright year
    M4=<command>            M4 executable (default: m4)
EOF
}


error()
{
    echo "error: $*" >&2
}


info()
{
    echo "[generate-estimator] $*"
}

# -----------------------------------------------------------------------------
# Project paths
# -----------------------------------------------------------------------------

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

TEMPLATE_INCLUDE_DIR="$ROOT_DIR/template/include/estimators"
TEMPLATE_SOURCE_DIR="$ROOT_DIR/template/src/estimators"

OUTPUT_INCLUDE_DIR="$ROOT_DIR/include/beast/estimators/"
OUTPUT_SOURCE_DIR="$ROOT_DIR/src/estimators/"


# -----------------------------------------------------------------------------
# Validate NAME
# -----------------------------------------------------------------------------

if [ "${NAME+x}" != "x" ]; then
    error "NAME variable is not set"
    usage >&2
    exit 2
fi

if [ -z "$NAME" ]; then
    error "NAME variable must not be empty"
    usage >&2
    exit 2
fi


# Only allow characters suitable for a C++ class/file identifier.
if [[ ! "$NAME" =~ ^[A-Za-z][A-Za-z0-9_]*$ ]]; then
    error "invalid NAME '$NAME'"
    error "NAME must start with a letter and contain only letters, numbers, and underscores"
    exit 2
fi

UPPER_NAME=$(printf '%s' "$NAME" | tr '[:lower:]' '[:upper:]')

# -----------------------------------------------------------------------------
# Configuration
# -----------------------------------------------------------------------------

M4="${M4:-m4}"
FORCE="${FORCE:-0}"
BEAST_YEAR="${BEAST_YEAR:-$(date +%Y)}"

BEAST_INCLUDE_BASEPATH="beast/estimators"

# Try to obtain author from Git if it was not explicitly provided.
if [ -z "${BEAST_AUTHOR:-}" ]; then
    BEAST_AUTHOR="$(
        git -C "$ROOT_DIR" config user.name 2>/dev/null || true
    )"
fi
if [ -z "$BEAST_AUTHOR" ]; then
    BEAST_AUTHOR="BEAST contributors"
fi

# Try to obtain repository URL from Git if it was not explicitly provided.
if [ -z "${BEAST_REPOSITORY:-}" ]; then
    BEAST_REPOSITORY="$(
        git -C "$ROOT_DIR" config --get remote.origin.url 2>/dev/null || true
    )"
fi
if [ -z "$BEAST_REPOSITORY" ]; then
    BEAST_REPOSITORY="https://github.com/delloiaconos/beast-cpp.git"
fi

# -----------------------------------------------------------------------------
# Check dependencies
# -----------------------------------------------------------------------------

if ! command -v "$M4" >/dev/null 2>&1; then
    error "M4 executable '$M4' was not found"
    error "Install GNU M4 or set M4=<path-to-m4>"
    exit 1
fi


# -----------------------------------------------------------------------------
# Template -> output mappings
#
# Add additional generated files here.
# -----------------------------------------------------------------------------

declare -A HEADER_FILES=(
    ["Estimator.h.m4"]="Estimator_${NAME}.h"
    ["Estimator_debug.h.m4"]="Estimator_${NAME}_debug.h"
)


declare -A SOURCE_FILES=(
    ["Estimator.cpp.m4"]="Estimator_${NAME}.cpp"
)


# -----------------------------------------------------------------------------
# Generation helpers
# -----------------------------------------------------------------------------

check_template()
{
    local template="$1"

    if [ ! -f "$template" ]; then
        error "template not found:"
        error "  $template"
        exit 1
    fi
}


check_output()
{
    local output="$1"

    if [ -e "$output" ] && [ "$FORCE" != "1" ]; then
        error "output file already exists:"
        error "  $output"
        error "Use FORCE=1 to overwrite existing files."
        exit 1
    fi
}


generate_file()
{
    local template="$1"
    local output="$2"

    check_template "$template"
    check_output "$output"

    info "Generating ${output#$ROOT_DIR/}"

    "$M4" \
        -D"BEAST_NAME=$NAME" \
        -D"BEAST_UPPER_NAME=$UPPER_NAME" \
        -D"BEAST_CLASS_NAME=Estimator_${NAME}" \
        -D"BEAST_AUTHOR=$BEAST_AUTHOR" \
        -D"BEAST_REPOSITORY=$BEAST_REPOSITORY" \
        -D"BEAST_YEAR=$BEAST_YEAR" \
        -D"BEAST_INCLUDE_BASEPATH=$BEAST_INCLUDE_BASEPATH" \
        "$template" > "$output"
}


# -----------------------------------------------------------------------------
# Validate all templates before creating anything
#
# This avoids partially generating a class because one of the templates was
# missing.
# -----------------------------------------------------------------------------

for template_name in "${!HEADER_FILES[@]}"; do
    check_template "$TEMPLATE_INCLUDE_DIR/$template_name"
done

for template_name in "${!SOURCE_FILES[@]}"; do
    check_template "$TEMPLATE_SOURCE_DIR/$template_name"
done


# -----------------------------------------------------------------------------
# Validate all output files before creating anything
# -----------------------------------------------------------------------------

for template_name in "${!HEADER_FILES[@]}"; do
    output_name="${HEADER_FILES[$template_name]}"
    check_output "$OUTPUT_INCLUDE_DIR/$output_name"
done

for template_name in "${!SOURCE_FILES[@]}"; do
    output_name="${SOURCE_FILES[$template_name]}"
    check_output "$OUTPUT_SOURCE_DIR/$output_name"
done


# -----------------------------------------------------------------------------
# Create output directories
# -----------------------------------------------------------------------------

mkdir -p "$OUTPUT_INCLUDE_DIR"
mkdir -p "$OUTPUT_SOURCE_DIR"


# -----------------------------------------------------------------------------
# Generate headers
# -----------------------------------------------------------------------------

for template_name in "${!HEADER_FILES[@]}"; do
    output_name="${HEADER_FILES[$template_name]}"

    generate_file \
        "$TEMPLATE_INCLUDE_DIR/$template_name" \
        "$OUTPUT_INCLUDE_DIR/$output_name"
done


# -----------------------------------------------------------------------------
# Generate sources
# -----------------------------------------------------------------------------

for template_name in "${!SOURCE_FILES[@]}"; do
    output_name="${SOURCE_FILES[$template_name]}"

    generate_file \
        "$TEMPLATE_SOURCE_DIR/$template_name" \
        "$OUTPUT_SOURCE_DIR/$output_name"
done


# -----------------------------------------------------------------------------
# Summary
# -----------------------------------------------------------------------------

echo
info "Estimator generated successfully"
info "Name:       $NAME"
info "Class:      Estimator_${UPPER_NAME}"
info "Headers:    ${OUTPUT_INCLUDE_DIR#$ROOT_DIR/}"
info "Sources:    ${OUTPUT_SOURCE_DIR#$ROOT_DIR/}"
info "Author:     $BEAST_AUTHOR"
info "Repository: $BEAST_REPOSITORY"
info "Year:       $BEAST_YEAR"

echo
info "Remember to register Estimator_${NAME} in the Estimator factory if"
info "the estimator must be selectable at runtime."