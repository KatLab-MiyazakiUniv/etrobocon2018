#!/bin/bash

chmod 755 clang-format.hook 
cp clang-format.hook ../.git/hooks/pre-commit
