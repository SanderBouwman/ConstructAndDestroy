#!/bin/bash

# Go to this script directory
cd $(dirname ${BASH_SOURCE[0]})

# Build and clean proposal
latexmk -lualatex project-plan.tex
if [ $? ]; then
  # Building executed with 0 thus we can clean working data
  latexmk -c project-plan.tex
fi
