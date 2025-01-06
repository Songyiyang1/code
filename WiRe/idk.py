import numpy as np

x = np.array([1.0, 2.0, 3.0, 4.0])
y = np.array([3.0, 2.0, 4.0, 1.0])
a = np.zeros(((x.size - 1) * 4, (x.size - 1) * 4))
a[0, 0], a[0, 1], a[-1, -4], a[-1, -3] = 6 * x[0], 2, 6 * x[- 1], 2  # natural boundary conditions
index = 0
for i in range(1, x.size * 4 - 7, 4):
    a[i, i - 1], a[i, i], a[i, i + 1], a[i, i + 2] = x[index] ** 3, x[index] ** 2, x[index], 1
    a[i + 1, i - 1], a[i + 1, i], a[i + 1, i + 1], a[i + 1, i + 2] = x[index + 1] ** 3, x[index + 1] ** 2, x[
        index + 1], 1
    a[i + 2, i - 1], a[i + 2, i], a[i + 2, i + 1], a[i + 2, i + 3], a[i + 2, i + 4], a[i + 2, i + 5] = 3 * x[
        index + 1] ** 2, 2 * x[index + 1], 1, -3 * x[index + 1] ** 2, -2 * x[index + 1], -1
    a[i + 3, i - 1], a[i + 3, i], a[i + 3, i + 3], a[i + 3, i + 4] = 6 * x[index + 1], 2, -6 * x[index + 2], -2
    index += 1

a[-3, -4], a[-3, -3], a[-3, -2], a[-3, -1] = x[-2] ** 3, x[-2] ** 2, x[-2], 1
a[-2, -4], a[-2, -3], a[-2, -2], a[-2, -1] = x[-1] ** 3, x[- 1] ** 2, x[- 1], 1  # the rest

'''print(x)
for i in range(a.shape[0]):
    print()
    for j in range(a.shape[1]):
        print(format(a[i,j],), end=" ")

print()'''
b = np.zeros(((x.size - 1) * 4))
index = 0
for i in range(1, x.size * 4 - 4, 4):
    b[i] = y[index]
    b[i + 1] = y[index + 1]
    index += 1
# TODO solve linear system for the coefficients of the spline
ans = np.linalg.solve(a, b)
spline = []
# TODO extract local interpolation coefficients from solution
for i in range(0, ans.size, 4):
    spline.append(np.poly1d(ans[i:i + 4]))

print(ans)
print(ans[7:4])
