import cs50
print("O hai! How much change is owed?")
while True:
    money = cs50.get_float()
    if money>=0:
        break
    else:
        print("How much change is owed?")
        continue
money = money * 100
q = money//25
d = (money%25)//10
n = (money - q*25 - d*10)//5
p = (money - q*25 - d*10 - n*5)
c = q + d + n + p
print(int(c))