import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import linprog
from matplotlib.lines import Line2D

# Objective function
c = np.array([3, -10])

# Boolean for min/max of objective function
minimize = False

# Constraints
A = np.array([
    [-2, 1],  # -2x1 + x2 <= 12
    [1, -3],  # x1 - 3x2 >= 3
    [6, 7],   # 6x1 + 7x2 <= 18
    [-3, 12], # -3x1 + 12x2 >= 8
    [2, -7],  # 2x1 - 7x2 <= 35
    [-1, 8],  # -x1 + 8x2 <= 29
    [-2, 6],  # -2x1 + 6x2 >= 9
])

b = np.array([12, -3, 18, 8, 35, 29, -9])

# Constraints' signs
signs = np.array([0, 1, 0, 1, 0, 0, 1])

# Bounds for the variables (x1 >= 0 and x2 >= 0)
bounds = [(0, None), (0, None)]

# Function to convert the equations to proper form
def fix_equations(A, b, signs, c, minimize):
    # Convert all inequalities of the form "Ax >= b" to "-Ax <= -b"
    for i in range(len(b)):
        if signs[i] == 1:
            A[i] = -A[i]
            b[i] = -b[i]
    
    # Convert maximization to minimization
    if not minimize:
        for i in range(len(c)):
            c[i] = -c[i]
    
    return A, b, c

# Function to solve the linear programming
def solve_lp(A, b, c, bounds):
    result = linprog(c, A_ub=A, b_ub=b, bounds=bounds)
    if result.success:
        return result.x
    else:
        return None

# Seidel Algorithm

# Fix equations
fix_equations(A, b, signs, c, minimize)

# Initialize with first 3 constraints and solve for them
initial_constraints_A = A[:3]
initial_constraints_b = b[:3]
x = solve_lp(initial_constraints_A, initial_constraints_b, c, bounds)

if x is None:
    print("No solution")
else:
    print(f"Initial solution: x1 = {x[0]:.3f}, x2 = {x[1]:.3f}")

# Increamentally add constraints
for i in range(3, A.shape[0]):
    if x is None:
        print("No solution")
        break
    
    # Check if the current solution satisfies all constraints up to the current one
    if np.all(np.dot(A[:i+1], x) <= b[:i+1]):
        continue
    else:
        # Otherwise, resolve including new constraint
        new_constraints_A = A[:i + 1]
        new_constraints_b = b[:i + 1]
        x = solve_lp(new_constraints_A, new_constraints_b, c, bounds)
        
        if x is None:
            print(f"No solution")
            break
        else:
            print(f"New solution: x1 = {x[0]:.3f}, x2 = {x[1]:.3f}")

# Plotting the feasible region
x1 = np.linspace(0, 20, 400)
x2 = np.linspace(0, 20, 400)

# Create a grid of points
X1, X2 = np.meshgrid(x1, x2)

plt.figure(figsize=(10, 8))

# Shading the regions corresponding to the constraints
plt.contourf(X1, X2, -2*X1 + X2 - 12, levels=[-np.inf, 0], colors='red', alpha=0.3)  # -2x1 + x2 <= 12
plt.contourf(X1, X2, X1 - 3*X2 - 3, levels=[-np.inf, 0], colors='blue', alpha=0.3)  # x1 - 3x2 >= 3
plt.contourf(X1, X2, 6*X1 + 7*X2 - 18, levels=[-np.inf, 0], colors='green', alpha=0.3)  # 6x1 + 7x2 <= 18
plt.contourf(X1, X2, -3*X1 + 12*X2 - 8, levels=[-np.inf, 0], colors='purple', alpha=0.3)  # -3x1 + 12x2 >= 8
plt.contourf(X1, X2, 2*X1 - 7*X2 - 35, levels=[-np.inf, 0], colors='orange', alpha=0.3)  # 2x1 - 7x2 <= 35
plt.contourf(X1, X2, -X1 + 8*X2 - 29, levels=[-np.inf, 0], colors='cyan', alpha=0.3)  # -x1 + 8x2 <= 29
plt.contourf(X1, X2, -2*X1 + 6*X2 - 9, levels=[-np.inf, 0], colors='brown', alpha=0.3)  # -2x1 + 6x2 >= 9

# Plot each constraint contour line (for boundaries)
plt.contour(X1, X2, -2*X1 + X2 - 12, levels=[0], colors='red')
plt.contour(X1, X2, X1 - 3*X2 - 3, levels=[0], colors='blue')
plt.contour(X1, X2, 6*X1 + 7*X2 - 18, levels=[0], colors='green')
plt.contour(X1, X2, -3*X1 + 12*X2 - 8, levels=[0], colors='purple')
plt.contour(X1, X2, 2*X1 - 7*X2 - 35, levels=[0], colors='orange')
plt.contour(X1, X2, -X1 + 8*X2 - 29, levels=[0], colors='cyan')
plt.contour(X1, X2, -2*X1 + 6*X2 - 9, levels=[0], colors='brown')

# Add axis labels and a grid
plt.xlabel('x1')
plt.ylabel('x2')
plt.xlim(0, 20)
plt.ylim(0, 20)
plt.axhline(0, color='black',linewidth=0.5)
plt.axvline(0, color='black',linewidth=0.5)
plt.grid(True)

# Plot the optimal solution points (if found)
if x is not None:
    plt.scatter(x[0], x[1], color='red', zorder=5, label=f"Optimal Solution: x1 = {x[0]:.3f}, x2 = {x[1]:.3f}")

# Manually add legend for constraints
handles = [Line2D([0], [0], color='red', lw=2),
           Line2D([0], [0], color='blue', lw=2),
           Line2D([0], [0], color='green', lw=2),
           Line2D([0], [0], color='purple', lw=2),
           Line2D([0], [0], color='orange', lw=2),
           Line2D([0], [0], color='cyan', lw=2),
           Line2D([0], [0], color='brown', lw=2)]
labels = ['-2x1 + x2 <= 12', 'x1 - 3x2 >= 3', '6x1 + 7x2 <= 18', '-3x1 + 12x2 >= 8',
          '2x1 - 7x2 <= 35', '-x1 + 8x2 <= 29', '-2x1 + 6x2 >= 9']

plt.legend(handles=handles, labels=labels, loc='best')

# Show the plot
plt.show()
