import numpy as np
import sys

def read_matrix(filename):
    with open(filename, 'r') as f:
        n = int(f.readline())
        data = np.loadtxt(f)
        return data.reshape((n, n))

if __name__ == "__main__":
    A = read_matrix("A.txt")
    B = read_matrix("B.txt")
    expected = A @ B # Перемножение через numpy
    
    actual = read_matrix("result.txt")
    
    if np.allclose(expected, actual, atol=1e-5):
        print("VERIFICATION SUCCESSFUL!")
    else:
        print("VERIFICATION FAILED!")
        sys.exit(1)
