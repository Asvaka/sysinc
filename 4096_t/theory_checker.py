for i in range(2, 4):
    for j in range(i, 10):
        print(f"Testing {i} * {j}:")
        print(f"{i}:")
        print(f"{i:08b}")
        print(f"{j}:")
        print(f"{j:08b}")
        print("Equals:")
        print(f"{i*j:08b}")
        print()
