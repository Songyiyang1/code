import numpy as np

A=np.arange(1,10,dtype=np.float64).reshape(3,3)
print(A)
print(A[1:, 1])
print(np.abs(A[1:, 1]))
print(np.argmax(np.abs(A[1:, 1])))
for j in range(0, A.shape[0]-1):
    for row in range(j + 1, A.shape[0]):
        A[row, :] -= A[row, j] / A[j, j]*A[j,:]
