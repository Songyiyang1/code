import numpy as np


####################################################################################################
# Exercise 1: Interpolation

def lagrange_interpolation(x: np.ndarray, y: np.ndarray) -> (np.poly1d, list):
    """
    Generate Lagrange interpolation polynomial.

    Arguments:
    x: x-values of interpolation points
    y: y-values of interpolation points

    Return:
    polynomial: polynomial as np.poly1d object
    base_functions: list of base polynomials
    """

    assert (x.size == y.size)

    polynomial = np.poly1d(0)
    base_functions = []

    # TODO: Generate Lagrange base polynomials and interpolation polynomial
    for i in range(x.size):
        base_functions.append(1)
        for j in range(x.size):
            if i != j:
                base_functions[i] *= np.poly1d([1, -x[j]]) / (x[i] - x[j])
        polynomial += y[i] * base_functions[i]
    return polynomial, base_functions


def hermite_cubic_interpolation(x: np.ndarray, y: np.ndarray, yp: np.ndarray) -> list:
    """
    Compute hermite cubic interpolation spline

    Arguments:
    x: x-values of interpolation points
    y: y-values of interpolation points
    yp: derivative values of interpolation points

    Returns:
    spline: list of np.poly1d objects, each interpolating the function between two adjacent points
    """

    assert (x.size == y.size == yp.size)

    spline = []
    # TODO compute piecewise interpolating cubic polynomials
    for i in range(x.size - 1):
        a = np.array([(x[i] ** 3, x[i] ** 2, x[i], 1), (x[i + 1] ** 3, x[i + 1] ** 2, x[i + 1], 1),
                      (3 * x[i] ** 2, 2 * x[i], 1, 0), (3 * x[i + 1] ** 2, 2 * x[i + 1], 1, 0)])
        b = np.array([y[i], y[i + 1], yp[i], yp[i + 1]])
        ans = np.linalg.solve(a, b)
        spline.append(np.poly1d(ans))
    return spline


####################################################################################################
# Exercise 2: Animation

def natural_cubic_interpolation(x: np.ndarray, y: np.ndarray) -> list:
    """
    Intepolate the given function using a spline with natural boundary conditions.

    Arguments:
    x: x-values of interpolation points
    y: y-values of interpolation points

    Return:
    spline: list of np.poly1d objects, each interpolating the function between two adjacent points
    """

    assert (x.size == y.size)
    # TODO construct linear system with natural boundary conditions
    a = np.zeros(((x.size - 1) * 4, (x.size - 1) * 4))

    index = 0
    for i in range(0, x.size * 4 - 10, 4):
        a[i, i], a[i, i+1], a[i, i + 2], a[i, i + 3] = x[index] ** 3, x[index] ** 2, x[index], 1
        a[i + 1, i], a[i + 1, i+ 1], a[i + 1, i + 2], a[i + 1, i +3] = x[index + 1] ** 3, x[index + 1] ** 2, x[
            index + 1], 1
        a[i + 2, i], a[i + 2, i+1], a[i + 2, i + 2], a[i + 2, i + 4], a[i + 2, i + 5], a[i + 2, i + 6] = 3 * x[
            index + 1] ** 2, 2 * x[index + 1], 1, -3 * x[index + 1] ** 2, -2 * x[index + 1], -1
        a[i + 3, i], a[i + 3, i+1], a[i + 3, i + 4], a[i + 3, i + 5] = 6 * x[index + 1], 2, -6 * x[index + 1], -2
        index += 1


    a[-4, -4], a[-4, -3], a[-4, -2], a[-4, -1] = x[-2] ** 3, x[-2] ** 2, x[-2], 1
    a[-3, -4], a[-3, -3], a[-3, -2], a[-3, -1] = x[-1] ** 3, x[- 1] ** 2, x[- 1], 1  # the rest
    a[-2, 0], a[-2, 1], a[-1, -4], a[-1, -3] = 6 * x[0], 2, 6 * x[- 1], 2  # natural boundary conditions
    '''
    print(x)
    for i in range(a.shape[0]):
        print()
        for j in range(a.shape[1]):
            print(format(a[i,j],), end=" ")
            
    print()'''
    b = np.zeros(((x.size - 1) * 4))
    index = 0
    for i in range(0, x.size * 4 - 4, 4):
        b[i] = y[index]
        b[i + 1] = y[index + 1]
        index += 1
    # TODO solve linear system for the coefficients of the spline
    ans = np.linalg.solve(a, b)
    spline = []
    # TODO extract local interpolation coefficients from solution
    for i in range(0, ans.size, 4):
        spline.append(np.poly1d(ans[i:i + 4]))
    return spline


def periodic_cubic_interpolation(x: np.ndarray, y: np.ndarray) -> list:
    """
    Interpolate the given function with a cubic spline and periodic boundary conditions.

    Arguments:
    x: x-values of interpolation points
    y: y-values of interpolation points

    Return:
    spline: list of np.poly1d objects, each interpolating the function between two adjacent points
    """

    assert (x.size == y.size)
    # TODO: construct linear system with periodic boundary conditions
    a = np.zeros(((x.size - 1) * 4, (x.size - 1) * 4))

    index = 0
    for i in range(0, x.size * 4 - 10, 4):
        a[i, i], a[i, i+1], a[i, i + 2], a[i, i + 3] = x[index] ** 3, x[index] ** 2, x[index], 1
        a[i + 1, i], a[i + 1, i+ 1], a[i + 1, i + 2], a[i + 1, i +3] = x[index + 1] ** 3, x[index + 1] ** 2, x[
            index + 1], 1
        a[i + 2, i], a[i + 2, i+1], a[i + 2, i + 2], a[i + 2, i + 4], a[i + 2, i + 5], a[i + 2, i + 6] = 3 * x[
            index + 1] ** 2, 2 * x[index + 1], 1, -3 * x[index + 1] ** 2, -2 * x[index + 1], -1
        a[i + 3, i], a[i + 3, i+1], a[i + 3, i + 4], a[i + 3, i + 5] = 6 * x[index + 1], 2, -6 * x[index + 1], -2
        index += 1

    a[-4, -4], a[-4, -3], a[-4, -2], a[-4, -1] = x[-2] ** 3, x[-2] ** 2, x[-2], 1
    a[-3, -4], a[-3, -3], a[-3, -2], a[-3, -1] = x[-1] ** 3, x[- 1] ** 2, x[- 1], 1  # the rest
    a[-2, 0], a[-2, 1],a[-2,2] ,a[-2, -4], a[-2, -3],a[-2,-2] = 3*x[0]**2,2*x[0],1,-3*x[-1]**2,-2*x[-1],-1
    a[-1,0],a[-1,1],a[-1,-4],a[-1,-3]=6*x[0],2,-6*x[-1],-2 # periodic boundary conditions
    b = np.zeros(((x.size - 1) * 4))
    index = 0
    for i in range(0, x.size * 4 - 4, 4):
        b[i] = y[index]
        b[i + 1] = y[index + 1]
        index += 1
    # TODO solve linear system for the coefficients of the spline
    ans = np.linalg.solve(a, b)
    spline = []
    # TODO extract local interpolation coefficients from solution
    for i in range( 0,ans.size, 4):
        spline.append(np.poly1d(ans[i:i + 4]))
    return spline


if __name__ == '__main__':
    x = np.array([1.0, 2.0, 3.0, 4.0])
    y = np.array([3.0, 2.0, 4.0, 1.0])

    splines = natural_cubic_interpolation(x, y)

    # # x-values to be interpolated
    # keytimes = np.linspace(0, 200, 11)
    # # y-values to be interpolated
    # keyframes = [np.array([0., -0.05, -0.2, -0.2, 0.2, -0.2, 0.25, -0.3, 0.3, 0.1, 0.2]),
    #              np.array([0., 0.0, 0.2, -0.1, -0.2, -0.1, 0.1, 0.1, 0.2, -0.3, 0.3])] * 5
    # keyframes.append(keyframes[0])
    # splines = []
    # for i in range(11):  # Iterate over all animated parts
    #     x = keytimes
    #     y = np.array([keyframes[k][i] for k in range(11)])
    #     spline = natural_cubic_interpolation(x, y)
    #     if len(spline) == 0:
    #         animate(keytimes, keyframes, linear_animation(keytimes, keyframes))
    #         self.fail("Natural cubic interpolation not implemented.")
    #     splines.append(spline)

    print("All requested functions for the assignment have to be implemented in this file and uploaded to the "
          "server for the grading.\nTo test your implemented functions you can "
          "implement/run tests in the file tests.py (> python3 -v test.py [Tests.<test_function>]).")
