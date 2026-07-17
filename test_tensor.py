import sys

# Look inside the 'build' folser for the compiled .so file
sys.path.append('./build')

# import the C++ library just like a standard Python package
import tensor_ext

print("✅ Successfully imported C++ tensor_ext modeule.\n")

print("Creating a 3x3 Matrix using the C++ engine...")
mat = tensor_ext.Matrix(3, 3) # Instantiate the C++ Matrix class from Python

print(f"Rows: {mat.get_rows()}") # Call some of the C++ methods
print(f"Cols: {mat.get_cols()}")

print("\nMatrix contents (safely intitialized to 0 by your C++ constructor):")
mat.print()

print("\n--- Testing Math ---")
A = tensor_ext.Matrix(2, 2)
A.set(0, 0, 1.0)
A.set(0, 1, 2.0)
A.set(1, 0, 3.0)
A.set(1, 1, 4.0)

B = tensor_ext.Matrix(2, 2)
B.set(0, 0, 2.0)
B.set(0, 1, 0.0)
B.set(1, 0, 0.0)
B.set(1, 1, 2.0)

print("Matrix A:")
A.print()

print("Matrix B:")
B.print()

print("\nA * B:")
C = A * B
C.print()
