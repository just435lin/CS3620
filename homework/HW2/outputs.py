# Python program to print all permutations using
# Heap's algorithm

# Generating permutation using Heap Algorithm
def heapPermutation(a, size):

	# if size becomes 1 then prints the obtained
	# permutation
	if size == 1:
		if isValid(a):  # I added this section to print only valid outputs 
			printArr(a) # and formatted correctly
		return

	for i in range(size):
		heapPermutation(a, size-1)

		# if size is odd, swap 0th i.e (first)
		# and (size-1)th i.e (last) element
		# else If size is even, swap ith
		# and (size-1)th i.e (last) element
		if size & 1:
			a[0], a[size-1] = a[size-1], a[0]
		else:
			a[i], a[size-1] = a[size-1], a[i]




# This code is contributed by ankush_953
# This code was cleaned up to by more pythonic by glubs9
# The above code was obtained from geeksforgeeks.org

def isValid(arr):
	passed1 = False
	passed2 = False
	for i in range(len(arr)):
		v = arr[i]
		if v==1: passed1=True
		if v==2: passed2=True
		if (v==3 or v==4) and passed1==False: return False
		if (v==5 or v==6) and passed2==False: return False
	return True

def printArr(arr):
	print("0", end= ", ")
	for i in range(len(arr)-1):
		print(arr[i], end= ", ")
	print(arr[len(arr)-1])

a = [1, 2, 3, 4, 5, 6]
n = len(a)
heapPermutation(a, n)
