#!/bin/bash
# Wrapper script to run J-Link provisioning from OEMiROT directory
# The actual scripts are in JLinkScripts subdirectory

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "J-Link Provisioning Scripts"
echo "==========================="
echo ""
echo "Available provisioning options:"
echo ""
echo "1. Python-based provisioning (recommended):"
echo "   python3 JLinkScripts/provision_jlink.py"
echo ""
echo "2. Hybrid approach (ST-LINK for OBKeys, J-Link for flash):"
echo "   bash JLinkScripts/provision_hybrid.sh"
echo ""
echo "For manual OBKey extraction:"
echo "   python3 JLinkScripts/extract_obkeys.py <obk_file>"
echo ""
echo "See JLinkScripts/README.md for detailed documentation"
echo ""

# Run the Python provisioning script by default
cd "$SCRIPT_DIR/JLinkScripts"
exec python3 provision_jlink.py "$@"
