#! /bin/bash

valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppressions.supp ./miniRT
