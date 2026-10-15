import os

os.system("podman build -t base64 .")

print()

command = "gcc " + input('File to compile: ') + " -lm -std=c89 -Wall -Wextra -Werror -Wpedantic -O2; ./a.out " + input('Test input: ')

print()

os.system('podman run base64 /bin/bash -c "' + command + '"')
