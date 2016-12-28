#!/bin/bash

# git submodule update
git submodule foreach 'git pull origin $(cat ../${PWD##*/}_tracking_name.txt)'
