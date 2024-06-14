#!/bin/bash
cat /etc/passwd
cat /etc/passwd > /tmp/usuarios
cd /tmp
cat /etc/passwd > ~/usuarios
cat /etc/group >> ~/usuarios
cat /etc/shells /etc/services > varios
cat