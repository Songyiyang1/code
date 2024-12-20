import numpy as np

import tomograph


####################################################################################################
# Exercise 1: Gaussian elimination

def gaussian_elimination(A: np.ndarray, b: np.ndarray, use_pivoting: bool = True) -> (np.ndarray, np.ndarray):
    """
    Gaussian Elimination of Ax=b with or without pivoting.

    Arguments:
    A : matrix, representing left side of equation system of size: (m,m)
    b : vector, representing right hand side of size: (m, )
    use_pivoting : flag if pivoting should be used

    Return:
    A : reduced result matrix in row echelon form (type: np.ndarray, size: (m,m))
    b : result vector in row echelon form (type: np.ndarray, size: (m, ))

    Raised Exceptions:
    ValueError: if matrix and vector sizes are incompatible, matrix is not square or pivoting is disabled but necessary

    Side Effects:
    -

    Forbidden:
    - numpy.linalg.*
    """
    # Create copies of input matrix and vector to leave them unmodified
    A = A.copy()
    b = b.copy()

    # TODO: Test if shape of matrix and vector is compatible and raise ValueError if not
    if A.shape[0] != b.shape[0] or A.shape[0] != A.shape[1]:
        raise ValueError()
    # TODO: Perform gaussian elimination
    for j in range(0, A.shape[0] - 1):  # j(+1)-th step of elimination
        if not use_pivoting:
            if A[j, j] == 0:
                raise ValueError()
        else:  # pivoting
            i_max = np.argmax(np.abs(A[j:, j])) + j  # +j because the index is now from j-th row!!!!!!!
            A[[j, i_max], :] = A[[i_max, j], :]  # switch the row
            b[[j, i_max]] = b[[i_max, j]]
        for row in range(j + 1, A.shape[0]):
            b[row] -= A[row, j] / A[j, j] * b[j]  # we must first compute b because A will change!!!!!!
            A[row, :] -= A[row, j] / A[j, j] * A[j, :]
    return A, b


def back_substitution(A: np.ndarray, b: np.ndarray) -> np.ndarray:
    """
    Back substitution for the solution of a linear system in row echelon form.

    Arguments:
    A : matrix in row echelon representing linear system
    b : vector, representing right hand side

    Return:
    x : solution of the linear system

    Raised Exceptions:
    ValueError: if matrix/vector sizes are incompatible or no/infinite solutions exist

    Side Effects:
    -

    Forbidden:
    - numpy.linalg.*
    """

    # TODO: Test if shape of matrix and vector is compatible and raise ValueError if not
    if A.shape[0] != b.shape[0]:
        raise ValueError()
    # TODO: Initialize solution vector with proper size
    x = np.zeros(A.shape[1])

    # TODO: Run backsubstitution and fill solution vector, raise ValueError if no/infinite solutions exist
    for row in range(A.shape[0] - 1, -1, -1):
        if A[row, row] == 0:
            raise ValueError()
        for i in A[row, :row]:
            if i != 0:
                raise ValueError()
        x[row] = b[row] / A[row, row]
        for i in range(0, row):
            b[i] -= x[row] * A[i, row]
    return x


####################################################################################################
# Exercise 2: Cholesky decomposition

def compute_cholesky(M: np.ndarray) -> np.ndarray:
    """
    Compute Cholesky decomposition of a matrix

    Arguments:
    M : matrix, symmetric and positive (semi-)definite

    Raised Exceptions:
    ValueError: L is not symmetric and psd

    Return:
    L :  Cholesky factor of M

    Forbidden:
    - numpy.linalg.*
    """

    # TODO check for symmetry and raise an exception of type ValueError
    (n, m) = M.shape
    if not np.allclose(np.transpose(np.matmul(np.transpose(M), M)), np.matmul(np.transpose(M), M)):
        raise ValueError()

    # TODO build the factorization and raise a ValueError in case of a non-positive definite input matrix

    L = np.zeros((n, n))
    for i in range(n):
        det = M[i, i] - np.sum(np.square(L[i, :i]))
        if det < 0:
            raise ValueError()
        else:
            L[i, i] = np.sqrt(det)
        for j in range(i + 1, n):
            L[j, i] = (M[j, i] - np.sum(L[i, :i] * L[j, :i])) / L[i, i]
    return L


def solve_cholesky(L: np.ndarray, b: np.ndarray) -> np.ndarray:
    """
    Solve the system L L^T x = b where L is a lower triangular matrix

    Arguments:
    L : matrix representing the Cholesky factor
    b : right hand side of the linear system

    Raised Exceptions:
    ValueError: sizes of L, b do not match
    ValueError: L is not lower triangular matrix

    Return:
    x : solution of the linear system

    Forbidden:
    - numpy.linalg.*
    """

    # TODO Check the input for validity, raising a ValueError if this is not the case
    (n, m) = L.shape
    if m != n: raise ValueError()
    for i in range(n):
        for j in range(i + 1, n):
            if L[i, j] != 0:
                raise ValueError()

    # TODO Solve the system by forward- and backsubstitution
    x = np.zeros(m)
    # fowardsubstitution:
    for row in range(n):
        if L[row, row] == 0:
            raise ValueError()
        x[row] = b[row] / L[row, row]
        for i in range(row + 1, n):
            b[i] -= x[row] * L[i, row]
    x = back_substitution(np.transpose(L), x)

    return x


####################################################################################################
# Exercise 3: Tomography

def setup_system_tomograph(n_shots: np.int64, n_rays: np.int64, n_grid: np.int64) -> (np.ndarray, np.ndarray):
    """
    Set up the linear system describing the tomographic reconstruction

    Arguments:
    n_shots : number of different shot directions
    n_rays  : number of parallel rays per direction
    n_grid  : number of cells of grid in each direction, in total n_grid*n_grid cells

    Return:
    L : system matrix
    g : measured intensities

    Raised Exceptions:
    -

    Side Effects:
    -

    Forbidden:
    -
    """

    # TODO: Initialize system matrix with proper size
    n = np.square(n_grid)
    m = n_rays
    k = n_shots
    L = np.zeros((m * k, n))
    # TODO: Initialize intensity vector
    g = np.zeros(m * k)

    # TODO: Iterate over equispaced angles, take measurements, and update system matrix and sinogram
    pi = np.float64(np.pi)
    for i in range(k):
        theta = pi / k * i
        intensities, ray_indices, isect_indices, lengths = tomograph.take_measurement(n_grid, n_rays, theta)
        g[i * m:(i + 1) * m] = intensities
        for j in range(len(ray_indices)):
            ray, cell, length = ray_indices[j], isect_indices[j], lengths[j]
            L[i * m + ray, cell] = length

    # Take a measurement with the tomograph from direction r_theta.
    # intensities: measured intensities for all <n_rays> rays of the measurement. intensities[n] contains the intensity for the n-th ray
    # ray_indices: indices of rays that intersect a cell
    # isect_indices: indices of intersected cells
    # lengths: lengths of segments in intersected cells
    # The tuple (ray_indices[n], isect_indices[n], lengths[n]) stores which ray has intersected which cell with which length. n runs from 0 to the amount of ray/cell intersections (-1) of this measurement.

    return [L, g]


def compute_tomograph(n_shots: np.int64, n_rays: np.int64, n_grid: np.int64) -> np.ndarray:
    """
    Compute tomographic image

    Arguments:
    n_shots : number of different shot directions
    n_rays  : number of parallel rays per direction
    n_grid  : number of cells of grid in each direction, in total n_grid*n_grid cells

    Return:
    tim : tomographic image

    Raised Exceptions:
    -

    Side Effects:
    -

    Forbidden:
    """

    # Setup the system describing the image reconstruction
    [L, g] = setup_system_tomograph(n_shots, n_rays, n_grid)
    # TODO: Solve for tomographic image using your Cholesky solver
    # (alternatively use Numpy's Cholesky implementation)

    #c=np.dot(np.dot(np.linalg.inv(np.dot(np.transpose(L),L)),np.transpose(L)),g)

    M=np.dot(np.transpose(L),L)
    b=np.dot(np.transpose(L),g)
    c=solve_cholesky(compute_cholesky(M),b)
    # TODO: Convert solution of linear system to 2D image
    tim = c.reshape(n_grid, n_grid)

    return tim


if __name__ == '__main__':
    print("All requested functions for the assignment have to be implemented in this file and uploaded to the "
          "server for the grading.\nTo test your implemented functions you can "
          "implement/run tests in the file tests.py (> python3 -v test.py [Tests.<test_function>]).")
