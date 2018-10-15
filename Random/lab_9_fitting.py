#fitting

def Gauss_Jor(a,n):
    #diagonalization
    for z in range(0,n):
        for x in range(0,n):
            if x!=z:
                ratio= float(a[x][z])/a[z][z]
                for y in range(0,n+1):
                    a[x][y]= a[x][y]-ratio*a[z][y]

    for s in range(n):
        div=a[s][s]
        a[s]=[x/div for x in a[s]]
    #Identity matrix creation

    sol=[0 for t in range(n)]
    for x in range(n):
        sol[x]=a[x][n]
    return(sol)


print("order of polynomial:")
n= int(input())
n = n+1
x=[0,1,2,3,4,5]
y=[2.1,7.7,13.6,27.2,40.9,61.1]

mat=[]

for i in range(n):
	sub=[]
	for j in range(n+1):
		z=0.0
		if(j/n!=1):
			for k in range(6):
				z+= x[k]**(i+j)
			sub.append(z)
		else:
			for m in range(6):
				z+= x[m]**i*y[m]
			sub.append(z)
	mat.append(sub)
	


print(mat)
sol = Gauss_Jor(mat,n)
print("\n")
print(sol)	
				

	
	



	
	
	
	
	
	
		
	
