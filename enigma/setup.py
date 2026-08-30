import os

invert = lambda r : [chr(p[1]+ord('A')) for p in sorted([(r[i],i) for i in range(26)])]

def main():
    file = open("/enigma.c", "r")

    while (not file.readline() == "\n"):
        pass

    inverted = []
    
    for i in range(3):
        i_post = invert(file.readline().split("\"")[1])
        post = ""
        for i in i_post:
            post += i
        inverted.append(post)

    os.system(f"vim 7G a {inverted[0]}")



if __name__ == "__main__":
    main();
