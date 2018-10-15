#Lab No:3
# Title : Jacobi and Gauss Seidel Method
# Date: 22/08/2017


print('No.of variables:')
n = int(input())
print('Elements of the Coefficient Matrix:')
a = [[0 for j in range(n)] for i in range(n)]

for i in range(n):
    for j in range(n):
        a[i][j]=float(input())

print('Enter the constant matrix:')
c=[0 for x in range(n)]
for x in range(n):
    c[x]=float(input())

print('Choose a method-')
print('Enter 0 for Jacobi Method')
print('Enter 1 for Gauss Seidel')


sol=[0 for x in range(n)]
sol_new=[0 for x in range(n)]
method=int(input())


while(1):
    for x in range(n):
        sum=0
        for i in range(n):
            if i!= x:
                if method==0:
                    sum=sum+a[x][i]*sol[i]
                else:
                    sum=sum+a[x][i]*sol_new[i]
        sol_new[x]=(c[x]-sum)/a[x][x]
    print(sol_new)

    new=[0 for x in range(n)]
    for x in range(n):
        new[x]=abs(sol_new[x]-sol[x])
    flag=0
    for i in range(n):
        if(new[i] < 0.0000000000000001):
            flag=flag+1
    if (flag==n):
        break

    for l in range(n):
        sol[l]=sol_new[l]
