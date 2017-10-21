import cs50

def get_positive_int():
    while True:
        n = cs50.get_int()
        if n>=1 and n<=23:
            break
        print("Retry: ", end="")
    return n
        
print("Height: ", end="")

n = get_positive_int()
for i in range(n):
    h = i+1
    s = n - h
    print(" " * s, end="")
    print("#" * h, end="")
    print("  ", end="")
    print("#" * h)