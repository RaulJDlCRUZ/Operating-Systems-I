#!/bin/bash
find ~/practicas/p2 -type f -perm 664 -name '*.h' -exec cp {} . \;