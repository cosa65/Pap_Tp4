permutation = [1, 2, 3, 4, 5, 0]
n = len(permutation)

results = [[i, j] for i in range(n) for j in range(i)]
iguales = []

for i in range(2**(n*(n-1)/2)):
	original = results[:]
	for j in range(n*(n-1)/2):
		if ((i >> j) & 1):
			original[j] = [original[j][1], original[j][0]]
	original.sort()

	permutado = original[:]
	for i in range(len(permutado)):
		permutado[i] = [permutation[permutado[i][0]], permutation[permutado[i][1]]]
	permutado.sort()
	if (original == permutado): iguales.append(original)

print len(iguales)
for i in iguales: print i
