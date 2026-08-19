#!/usr/bin/env bash

# BEAST - Battery Estimation Architecture and Simulation Toolkit
#
# BEAST is a C++ framework for battery modeling, simulation, and
# state/parameter estimation.
#
# This script installs FMPP locally as a BEAST development tool.
#
# Copyright (c) 2026 Salvatore Dello Iacono.
# Licensed under the GNU General Public License v3.0.
#
# Project: https://github.com/delloiaconos/beast-cpp.git

# Stop the script immediately if a command fails.
set -e

FMPP_VERSION="0.9.16"

# Resolve all paths relative to the directory containing this script.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TARGET_DIR="${SCRIPT_DIR}/fmpp_${FMPP_VERSION}"
TEMP_DIR="${SCRIPT_DIR}/.temp"
TMP_ZIP="${TEMP_DIR}/fmpp_${FMPP_VERSION}.zip"
FMPP_EXTRACTED_DIR="${TEMP_DIR}/fmpp_${FMPP_VERSION}"

# Direct download URL using the SourceForge mirror system.
DOWNLOAD_URL="https://downloads.sourceforge.net/project/fmpp/fmpp/${FMPP_VERSION}/fmpp_${FMPP_VERSION}.zip?use_mirror=autoselect"

echo "=== Local FMPP Installation ==="

# 1. Check system prerequisites.
if ! command -v java &> /dev/null; then
    echo "Error: Java is not installed. FMPP requires a Java runtime environment (JRE/JDK)."
    exit 1
fi

if ! command -v unzip &> /dev/null; then
    echo "Error: the 'unzip' utility is not installed (for example: sudo apt install unzip)."
    exit 1
fi

# Create the destination and local temporary directories if needed.
mkdir -p "${TEMP_DIR}"
mkdir -p "${TARGET_DIR}"

# 2. Reuse an already downloaded archive when available.
if [ -f "${TMP_ZIP}" ]; then
    echo "FMPP archive already exists: ${TMP_ZIP}"
    echo "Skipping download."
else
    echo "Downloading FMPP v${FMPP_VERSION}..."

    DOWNLOAD_OK=false

    if command -v curl &> /dev/null; then
        # -f makes curl fail on HTTP errors such as 404.
        # -L follows SourceForge redirects.
        if curl -f -L "${DOWNLOAD_URL}" -o "${TMP_ZIP}"; then
            DOWNLOAD_OK=true
        else
            echo "Warning: curl download failed. Trying wget if available..."
            rm -f "${TMP_ZIP}"
        fi
    fi

    if [ "${DOWNLOAD_OK}" = false ] && command -v wget &> /dev/null; then
        if wget -O "${TMP_ZIP}" "${DOWNLOAD_URL}"; then
            DOWNLOAD_OK=true
        else
            rm -f "${TMP_ZIP}"
        fi
    fi

    if [ "${DOWNLOAD_OK}" = false ]; then
        echo "Error: FMPP could not be downloaded with either curl or wget."
        exit 1
    fi
fi

# Verify that the archive exists and is not empty.
if [ ! -s "${TMP_ZIP}" ]; then
    echo "Error: the FMPP archive '${TMP_ZIP}' does not exist or is empty."
    rm -f "${TMP_ZIP}"
    exit 1
fi

# Verify that the archive is a valid ZIP file before extracting it.
if ! unzip -tq "${TMP_ZIP}" > /dev/null; then
    echo "Error: the FMPP archive '${TMP_ZIP}' is not a valid ZIP file."
    echo "Remove the invalid archive and run the installer again."
    exit 1
fi

# 3. Extract the archive inside the local temporary directory.
echo "Extracting ${TMP_ZIP} into ${TEMP_DIR}..."
rm -rf "${FMPP_EXTRACTED_DIR}"
unzip -q "${TMP_ZIP}" -d "${FMPP_EXTRACTED_DIR}"

if [ ! -d "${FMPP_EXTRACTED_DIR}" ]; then
    echo "Error: expected extracted directory '${FMPP_EXTRACTED_DIR}' was not found."
    exit 1
fi

# 4. Copy and reorganize the required files.
echo "Installing files into ${TARGET_DIR}..."
cp -r \
    "${FMPP_EXTRACTED_DIR}/fmpp/bin" \
    "${FMPP_EXTRACTED_DIR}/fmpp/lib" \
    "${FMPP_EXTRACTED_DIR}/fmpp/docs" \
    "${FMPP_EXTRACTED_DIR}/fmpp/readme.txt" \
    "${FMPP_EXTRACTED_DIR}/fmpp/LICENSE.txt" \
    "${TARGET_DIR}/"

# 5. Remove only the extracted directory.
# Keep the ZIP archive in TEMP_DIR so future runs can reuse it.
echo "Removing extracted temporary files..."
rm -rf "${FMPP_EXTRACTED_DIR}"

# 6. Configure Linux execute permissions.
chmod +x "${TARGET_DIR}/bin/fmpp"

echo "=== FMPP Installation Completed Successfully ==="
echo "Cached archive: ${TMP_ZIP}"
echo "Check the installed version with: ${TARGET_DIR}/bin/fmpp --version"
