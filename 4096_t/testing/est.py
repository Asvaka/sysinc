import os

os.system("podman build -t tester .")

print()
print()
print()

os.system("podman run tester python3 tester.py")
