import matplotlib.pyplot as plt
import random
import copy
import math
import time
import numpy as np

from scipy.spatial import ConvexHull
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

# 2D Convex Hull

# Function to plot points and convex hull
def plot(points, convex_hull):
    # Extract x and y 
    point_x, point_y = zip(*points)
    hull_x, hull_y = zip(*convex_hull)

    # Plot the points
    plt.scatter(point_x, point_y, color='blue', label='Points')

    # Plot the convex hull
    plt.plot(list(hull_x) + [hull_x[0]], list(hull_y) + [hull_y[0]], color='red', label='Convex Hull')

    # Show plot
    plt.title("Convex Hull")
    plt.xlabel("X")
    plt.ylabel("Y")

    plt.legend()
    plt.grid(True)
    plt.show()

# Function to return the ccw of 3 points
def ccw(p0, p1, p2):
    det = (p1[0] - p0[0]) * (p2[1] - p0[1]) - (p2[0] - p0[0]) * (p1[1] - p0[1])
    if det == 0:
        return 0    # Collinear
    elif det > 0:
        return 1    # CCW
    else:
        return 2    # CW

# Graham Scan Algorithm
def graham_scan(points):
   
    P = copy.deepcopy(points)

    # Sort P
    P = sorted(P)

    # Initialize upper and lower hull
    upper_hull = [P[0], P[1]]
    lower_hull = [P[-1], P[-2]]

    # Build the hulls
    for i in range(2, len(P)):
        upper_hull.append(P[i])
        while len(upper_hull) >= 3 and ccw(upper_hull[-3], upper_hull[-2], upper_hull[-1]) != 2:
            upper_hull.pop(-2)
    
    for i in range(len(P) - 3, 0, -1):
        lower_hull.append(P[i])
        while len(lower_hull) >= 3 and ccw(lower_hull[-3], lower_hull[-2], lower_hull[-1]) != 2:
            lower_hull.pop(-2)

    # Remove the first and last points of the lower hull
    lower_hull.pop(-1)
    lower_hull.pop(0)

    # Merge hulls and return
    return upper_hull + lower_hull

# Gift Wrapping Algorithm
def gift_wrapping(points):

    S = copy.deepcopy(points)

    # Initialize r and chain of points 
    r0 = min(S)
    r = r0
    chain = [r]

    # Main loop
    while True:
        # Initialize u with a non-vertex
        u = random.choice([p for p in S if p != r])
        
        # Iterate each point t
        for t in [p for p in S if p != u]:
            # if cw or r,u,t collinear and u in between r,t
            if ccw(r, u, t) == 2 or (ccw(r, u, t) == 0 and min(r[0], t[0]) <= u[0] <= max(r[0], t[0]) and min(r[1], t[1]) <= u[1] <= max(r[1], t[1])):
                u = t

        # Exit condition
        if u == r0:
            break
        else:
            r = u
            chain.append(r)
            S.remove(r)

    return chain

# Function to find the upper bridge of 2 convex hulls
def upper_bridge(A, B):

    # Default case: both A and B have more than 2 points
    if len(A) > 2 and len(B) > 2:
        i = A.index(max(A)) # Rightmost point in A
        j = B.index(min(B)) # Leftmost point in B

        while True:
            changed = False
            # Check if the line from A[i] to A[i+1] leaves B[j] and A[i+2] in the same half-plane
            if ccw(A[i], A[(i + 1) % len(A)], B[j]) != ccw(A[i], A[(i + 1) % len(A)], A[(i + 2) % len(A)]):
                i = (i + 1) % len(A)
                changed = True

            # Check if the line from B[j] to B[j-1] leaves A[i] and B[j-2] in the same half-plane
            if ccw(B[j], B[(j - 1) % len(B)], A[i]) != ccw(B[j], B[(j - 1) % len(B)], B[(j - 2) % len(B)]):
                j = (j - 1) % len(B)
                changed = True

            # Upper bridge found
            if not changed:
                return A[i], B[j]

    # Case when A or B have exactly 2 points
    if len(A) == 2 and len(B) == 2:
        # Upper bridge is the two uppermost points from both A and B
        upper_A = max(A, key=lambda p: p[1])
        upper_B = max(B, key=lambda p: p[1])
        return upper_A, upper_B

    # If A has 2 points, extract its highest point and process B normally
    if len(A) == 2:
        upper_A = max(A, key=lambda p: p[1])    # Highest point in A
        i = A.index(upper_A)
        
        # Process B normally
        j = B.index(min(B))
        while True:
            changed = False

            if ccw(B[j], B[(j - 1) % len(B)], A[i]) != ccw(B[j], B[(j - 1) % len(B)], B[(j - 2) % len(B)]):
                j = (j - 1) % len(B)
                changed = True

            if not changed:
                return A[i], B[j]

    # If B has 2 points, extract its highest point and process A normally
    if len(B) == 2:
        upper_B = max(B, key=lambda p: p[1])    # Highest point in B
        j = B.index(upper_B)

        # Process A normally
        i = A.index(max(A))  # Rightmost point in A
        while True:
            changed = False
            if ccw(A[i], A[(i + 1) % len(A)], B[j]) != ccw(A[i], A[(i + 1) % len(A)], A[(i + 2) % len(A)]):
                i = (i + 1) % len(A)
                changed = True

            if not changed:
                return A[i], B[j]

# Function to find the lower bridge of 2 convex hulls
def lower_bridge(A, B):

    # Default case: both A and B have more than 2 points
    if len(A) > 2 and len(B) > 2:
        i = A.index(max(A))  # Rightmost point in A
        j = B.index(min(B))  # Leftmost point in B

        while True:
            changed = False
            # Check if the line from A[i] to A[i-1] leaves B[j] and A[i-2] in the same half-plane
            if ccw(A[i], A[(i - 1) % len(A)], B[j]) != ccw(A[i], A[(i - 1) % len(A)], A[(i - 2) % len(A)]):
                i = (i - 1) % len(A)
                changed = True

            # Check if the line from B[j] to B[j+1] leaves A[i] and B[j+2] in the same half-plane
            if ccw(B[j], B[(j + 1) % len(B)], A[i]) != ccw(B[j], B[(j + 1) % len(B)], B[(j + 2) % len(B)]):
                j = (j + 1) % len(B)
                changed = True

            # Lower bridge found
            if not changed:
                return A[i], B[j]

    # Case when A or B has exactly 2 points
    if len(A) == 2 and len(B) == 2:
        # Lower bridge is the two lowermost points from both A and B
        lower_A = min(A, key=lambda p: p[1])
        lower_B = min(B, key=lambda p: p[1])
        return lower_A, lower_B

    # If A has 2 points, extract its lowest point and process B normally
    if len(A) == 2:
        lower_A = min(A, key=lambda p: p[1])  # Lowest point in A
        i = A.index(lower_A)
        # Process B normally
        j = B.index(min(B))  # Leftmost point in B
        while True:
            changed = False

            if ccw(B[j], B[(j + 1) % len(B)], A[i]) != ccw(B[j], B[(j + 1) % len(B)], B[(j + 2) % len(B)]):
                j = (j + 1) % len(B)
                changed = True

            if not changed:
                return A[i], B[j]

    # If B has 2 points, extract its lowest point and process A normally
    if len(B) == 2:
        lower_B = min(B, key=lambda p: p[1])  # Lowest point in B
        j = B.index(lower_B)
        # Process A normally
        i = A.index(max(A))  # Rightmost point in A
        while True:
            changed = False
            if ccw(A[i], A[(i - 1) % len(A)], B[j]) != ccw(A[i], A[(i - 1) % len(A)], A[(i - 2) % len(A)]):
                i = (i - 1) % len(A)
                changed = True

            if not changed:
                return A[i], B[j]

# Function to sort points in ccw order
def sort_ccw(points):

    # Find the bottommost rightmost point and move it at the beginning
    p0 = min(points, key=lambda p: (p[1], p[0]))
    points.remove(p0)
    points.insert(0, p0)
    
    # Bubble sort logic
    # If points are cw, then swap them to make them ccw
    n = len(points)
    swapped = True
    
    while swapped:
        swapped = False
        for i in range(1, n-1):
            # Check the ccw for points (p0, points[i], points[i+1])
            if ccw(p0, points[i], points[i+1]) == 2:  # If the turn is cw
                # Swap points[i] and points[i+1]
                points[i], points[i+1] = points[i+1], points[i]
                swapped = True
    
    return points

# Divide & Conquer Algorithm
def divide_conquer(p):

    points = copy.deepcopy(p)

    # Sort points
    points = sorted(points)

    # Base case
    if len(points) == 3:
        return sort_ccw(points)
    elif len(points) == 2:
        return points
    
    # Split points
    mid = len(points) // 2
    A = points[:mid]
    B = points[mid:]

    # Recursion
    convex_hull_A = sort_ccw(divide_conquer(A))
    convex_hull_B = sort_ccw(divide_conquer(B))
       
    # Find bridges
    upper_bridge_points = upper_bridge(convex_hull_A, convex_hull_B)
    lower_bridge_points = lower_bridge(convex_hull_A, convex_hull_B)

    # Merge
    convex_hull = []

    # Get the indexes of the bridges
    upperA = convex_hull_A.index(upper_bridge_points[0])
    upperB = convex_hull_B.index(upper_bridge_points[1])

    lowerA = convex_hull_A.index(lower_bridge_points[0])
    lowerB = convex_hull_B.index(lower_bridge_points[1])

    # Start from upperA, insert all points ccw till lowerA,
    # then jump to lowerB and insert ccw till upperB

    i = upperA
    while True:
        convex_hull.append(convex_hull_A[i])

        if i == lowerA:
            break

        i = (i + 1) % len(convex_hull_A)        

    i = lowerB
    while True:
        convex_hull.append(convex_hull_B[i])

        if i == upperB:
            break

        i = (i + 1) % len(convex_hull_B)
        
    return convex_hull

# Quickhull Algorithm
def quickhull(p):

    points = copy.deepcopy(p)

    convex_hull = []

    # Find the leftmost, rightmost, topmost, and bottommost points
    left_point = min(points, key=lambda p: p[0])    # leftmost
    right_point = max(points, key=lambda p: p[0])   # rightmost
    top_point = min(points, key=lambda p: p[1])     # topmost
    bottom_point = max(points, key=lambda p: p[1])  # bottommost

    # Add the four boundary points to the convex hull
    convex_hull.append(left_point)
    convex_hull.append(right_point)
    convex_hull.append(top_point)
    convex_hull.append(bottom_point)

    # Find the convex hull for each region
    top_left_hull = quickhull_recursive(left_point, top_point, points)
    top_right_hull = quickhull_recursive(top_point, right_point, points)
    bottom_left_hull = quickhull_recursive(left_point, bottom_point, points)
    bottom_right_hull = quickhull_recursive(bottom_point, right_point, points)

    # Merge the hulls from each region
    convex_hull += top_left_hull
    convex_hull += top_right_hull
    convex_hull += bottom_left_hull
    convex_hull += bottom_right_hull

    # Sort the points in ccw order
    return sort_ccw(convex_hull)

# Function to find the distance between a point and a line
def distance(a, b, p): 
    return  (abs(((b[0] - a[0]) * (a[1] - p[1])) - ((a[0] - p[0]) * (b[1] - a[1])))) / math.sqrt((pow((b[0] - a[0]), 2)) + (pow((b[1] - a[1]), 2)))

# Helper function for quickhull recursion
def quickhull_recursive(a, b, points):

    if not points:
        return []

    # Points left to be checked in the recursive part
    recursive_points = []
    # Convex hull points
    convex_hull_points = []

    furthest_point = []
    
    # Find furthest point from AB
    max_dis = 0.0
    for point in points:
        if ccw(a, b, point) == 1:
            recursive_points.append(point)
            dis = distance(a, b, point)
            if (dis > max_dis):
                max_dis = dis
                furthest_point = point

    if furthest_point:
        convex_hull_points.append(furthest_point)

    # Recursion in the subareas created by the furthest point
    s1 = quickhull_recursive(a, furthest_point, recursive_points)
    s2 = quickhull_recursive(furthest_point, b, recursive_points)

    convex_hull_points += s1
    convex_hull_points += s2

    return convex_hull_points

# Function to generate random points and ensure no three points are collinear
def generate_random_points(n):
    points = []
    while len(points) < n:
        # Create a random point between -100 and 100
        x = random.randint(-100, 100)
        y = random.randint(-100, 100)
        point = (x, y)
        
        # Check if the new point causes collinearity with any two other points already in the list
        collinear = False
        for i in range(len(points)):
            for j in range(i + 1, len(points)):
                if ccw(points[i], points[j], point) == 0:
                    collinear = True
                    break
            if collinear:
                break
        
        if not collinear:
            points.append(point)
    
    return points

# Function to run a specific algorithm and compute its runtime
def time_algorithm(algorithm, points):
    start_time = time.time()
    result = algorithm(points)
    end_time = time.time()
    return result, end_time - start_time

# Function to run all algorithms for different points count and showcase their results
def run_tests():
    count = [10, 20, 50, 100, 200]
    results = []

    for n in count:
        # Generate random points for each test case
        points = generate_random_points(n)

        # Measure time for each algorithm
        graham_points, graham_time = time_algorithm(graham_scan, points)
        # plot(points, graham_points)
        gift_points, gift_time = time_algorithm(gift_wrapping, points)
        # plot(points, gift_points)
        dc_points, dc_time = time_algorithm(divide_conquer, points)
        # plot(points, dc_points)
        quick_points, quick_time = time_algorithm(quickhull, points)
        # plot(points, quick_points)

        # Store the results
        results.append({
            "Points": n,
            "Graham Scan": graham_time,
            "Gift Wrapping": gift_time,
            "Divide & Conquer": dc_time,
            "Quickhull": quick_time
        })
    print("finished")

    print(f"{'Points'}      {'Graham Scan':<15} {'Gift Wrapping':<15} {'Divide Conquer':<15}  {'Quickhull':<15}")
    for result in results:
        print(f"{result['Points']}          {result['Graham Scan']:.6f}         {result['Gift Wrapping']:.6f}       {result['Divide & Conquer']:.6f}        {result['Quickhull']:.6f}")

# Run the test
run_tests()

# 3D Convex Hull

# Function to compute the orientation of 3 points in 3D
def ccw_3d(p0, p1, p2):
    v1 = np.array(p1) - np.array(p0)
    v2 = np.array(p2) - np.array(p0)
    cross_prod = np.cross(v1, v2)
    return cross_prod

# Quickhull 3D Algorithm
def quickhull_3d(points):
    points = np.array(points)
    
    # Find extreme points in each dimension (leftmost, rightmost, etc.)
    leftmost = min(points, key=lambda p: p[0])
    rightmost = max(points, key=lambda p: p[0])
    
    # Define the initial convex hull using the extreme points
    def quickhull_recursive(a, b, points_subset):
        if not points_subset:
            return []
        
        max_distance = -1
        furthest_point = None
        for point in points_subset:
            # Compute the perpendicular distance from point to the line (a, b)
            distance = np.linalg.norm(np.cross(b - a, point - a)) / np.linalg.norm(b - a)
            if distance > max_distance:
                max_distance = distance
                furthest_point = point
        
        # Split points into two sets: one on the left and one on the right of the line
        remaining_points = [point for point in points_subset if not np.array_equal(point, a) and not np.array_equal(point, b) and not np.array_equal(point, furthest_point)]
        
        above = []
        below = []
        for point in remaining_points:
            if np.dot(ccw_3d(a, furthest_point, point), np.cross(b - a, furthest_point - a)) > 0:
                above.append(point)
            else:
                below.append(point)
        
        # Recursively call the function for above and below the plane
        hull_points = quickhull_recursive(a, furthest_point, above) + [furthest_point] + quickhull_recursive(furthest_point, b, below)
        return hull_points
    
    # Find the convex hull of the points using the recursive method
    points_left = [p for p in points if not np.array_equal(p, leftmost) and not np.array_equal(p, rightmost)]
    hull_left = quickhull_recursive(leftmost, rightmost, points_left)
    
    points_right = [p for p in points if not np.array_equal(p, rightmost) and not np.array_equal(p, leftmost)]
    hull_right = quickhull_recursive(rightmost, leftmost, points_right)

    # Combine both hulls and return the result
    return [leftmost] + hull_left + [rightmost] + hull_right


# Function to plot the 3D convex hull
def plot_3d_hull(points, hull_points):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    # Unzip the points and hull points
    x_points, y_points, z_points = zip(*points)
    x_hull, y_hull, z_hull = zip(*hull_points)
    
    # Plot the points
    ax.scatter(x_points, y_points, z_points, color='blue', label="Points")
    
    # Compute the convex hull for plotting
    points_hull = np.array(hull_points)
    hull = ConvexHull(points_hull)
    
    # Plot the convex hull faces
    for simplex in hull.simplices:
        face = [points_hull[simplex[0]], points_hull[simplex[1]], points_hull[simplex[2]]]
        ax.add_collection3d(Poly3DCollection([face], facecolors='cyan', linewidths=1, edgecolors='r', alpha=0.5))
    
    # Add labels and title
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    ax.set_title("3D Convex Hull")
    
    plt.legend()
    plt.show()

# Example: Generate random points and compute the convex hull
points = [(random.randint(-10, 10), random.randint(-10, 10), random.randint(-10, 10)) for _ in range(80)]

hull = quickhull_3d(points)

# Plot the 3D convex hull
plot_3d_hull(points, hull)
