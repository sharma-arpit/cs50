def main():
    N = int(input())
    list = [int(x) for x in input().split()]
    m = 1000000007
    f = multiply(list, m)
    g = GCD(list)
    p = power(f, g, m)
    print(p)
    
def power(a, n, m):
    
    if n==0:
        return 1
    elif n%2==0:
        return power((a*a)%m, n/2, m)
    else:
        return a*power((a*a)%m, (n-1)/2, m)
    
def multiply(list, m):
    result = 1
    for i in range(len(list)):
        result = (result*list[i])%m
    
    return result
    
def GCD(list):
    list.sort()
    counter = 0 
    minimum = list[0]
    for i in reversed(range(1, minimum+1)):
        for j in range(len(list)):
            if list[j]%minimum==0:
                counter+=1
            else:
                break
        if counter == len(list):
            return i
    
if __name__ == "__main__":
    main()