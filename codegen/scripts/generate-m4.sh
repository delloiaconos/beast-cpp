#!/usr/bin/env bash

# SPDX-License-Identifier: GPL-3.0-only
#
# BEAST - Battery Estimation Architecture and Simulation Toolkit
#
# Generate the source and header files for a new class from M4 templates.
#
# Usage:
#
#   NAME=R0R1C1 scripts/generate.sh config.conf
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
#   NAME=R0R1C1 \
#   BEAST_AUTHOR="Salvatore Dello Iacono" \
#   scripts/generate.sh config.conf
#

set -euo pipefail


# -----------------------------------------------------------------------------
# Utility functions
# -----------------------------------------------------------------------------

usage()
{
    cat <<EOF
Usage:
    NAME=<model-name> $(basename "$0") config.conf

Example:
    NAME=R0R2C2 $(basename "$0") config.conf

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
    echo "[generate] $*"
}

# -----------------------------------------------------------------------------
# Project paths
# -----------------------------------------------------------------------------

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

CODEGEN_DIR="$ROOT_DIR/codegen/m4"


# -----------------------------------------------------------------------------
# Check config file argument
# -----------------------------------------------------------------------------

if [[ $# -lt 1 ]]; then
    error "config file missing"
    usage >&2
    exit 2
fi

CONFIG_FILE="$1"

# -----------------------------------------------------------------------------
# Validate configuration file
# -----------------------------------------------------------------------------

if [[ ! -f "$CONFIG_FILE" ]]; then
    echo "Error: configuration file not found: $CONFIG_FILE"
    exit 1
fi

# -----------------------------------------------------------------------------
# Load generation definition
# -----------------------------------------------------------------------------

source "$CONFIG_FILE"

if [[ ${#FILES[@]} -eq 0 ]]; then
    echo "Error: no files defined in $CONFIG_FILE"
    exit 1
fi

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

BEAST_INCLUDE_BASEPATH="beast/cell_models"

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
        -D"BEAST_UPNAME=$UPPER_NAME" \
        -D"BEAST_CLASS_NAME=${CLASSNAME}_${NAME}" \
        -D"BEAST_AUTHOR=$BEAST_AUTHOR" \
        -D"BEAST_REPOSITORY=$BEAST_REPOSITORY" \
        -D"BEAST_YEAR=$BEAST_YEAR" \
        -D"BEAST_INCLUDE_BASEPATH=$BEAST_INCLUDE_BASEPATH" \
        "$template" > "$output"
}


# -----------------------------------------------------------------------------
# Validate templates
# -----------------------------------------------------------------------------

for entry in "${FILES[@]}"; do
    IFS='|' read -r template_file output_file <<< "$entry"
    check_template "$template_file"
done


# -----------------------------------------------------------------------------
# Validate all output files before creating anything
# -----------------------------------------------------------------------------

for entry in "${FILES[@]}"; do
    IFS='|' read -r template_file output_file <<< "$entry"
    check_output "$output_file"
done


# -----------------------------------------------------------------------------
# Create output directories
# -----------------------------------------------------------------------------

for entry in "${FILES[@]}"; do
    IFS='|' read -r template_file output_file <<< "$entry"
    mkdir -p "$(dirname "$output_file")"
done


# -----------------------------------------------------------------------------
# Generate files
# -----------------------------------------------------------------------------

for entry in "${FILES[@]}"; do
    IFS='|' read -r template_file output_file <<< "$entry"

    generate_file \
        "$template_file" \
        "$output_file"
done



# -----------------------------------------------------------------------------
# Summary
# -----------------------------------------------------------------------------

echo
info "${CLASSNAME} generated successfully"
info "Name:       $NAME"
info "Class:      ${CLASSNAME}_${UPPER_NAME}"
info "Author:     $BEAST_AUTHOR"
info "Repository: $BEAST_REPOSITORY"
info "Year:       $BEAST_YEAR"

echo
info "Remember to register ${CLASSNAME}_${NAME} in the ${CLASSNAME} factory if"
info "the model must be selectable at runtime."