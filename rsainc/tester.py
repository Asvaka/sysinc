import os

os.system("podman build -t rsainc .")

print()

command = "gcc " + input('File to compile: ') + " -lm -std=c89 -Wall -Wextra -Werror -Wpedantic -O2; ./a.out; python3 testing.py"

print()

os.system('podman run rsainc /bin/bash -c "' + command + '"')
