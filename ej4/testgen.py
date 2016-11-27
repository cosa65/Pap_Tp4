#posib = [[3], [5], [7], [1]*2, [1]*3, [1]*4, [1]*5, [1]*6, [1]*7, [3, 1], [3]+[1]*2, [3]+[1]*3, [3]+[1]*4, [3]*2, [3]*2+[1], [5, 1], [5, 1, 1]]
i = input()
print sum(i)
mn = 1;
for j in i:
	serie = range(mn, mn + j)
	serie = serie[1:]+[serie[0]]
	for i in serie: print i,
	mn += j
print '\n',
