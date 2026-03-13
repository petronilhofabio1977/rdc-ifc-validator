#!/bin/bash
set -e

INPUT="rdc_report.txt"
OUTPUT="rdc_report.pdf"

enscript "$INPUT" -o - | ps2pdf - "$OUTPUT"

echo "PDF gerado: $OUTPUT"
