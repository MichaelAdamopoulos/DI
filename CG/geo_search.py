import matplotlib.pyplot as plt
import numpy as np

# Κατασκευή κόμβου για το kd-tree
class KDTreeNode:
    def __init__(self, point, left=None, right=None):
        self.point = point  # Το σημείο του κόμβου
        self.left = left    # Αριστερό υποδέντρο
        self.right = right  # Δεξί υποδέντρο

# Συνάρτηση για την κατασκευή του kd-tree
def build_kd_tree(points, depth=0):
    if not points:
        return None

    # Επιλογή του άξονα (εναλλάσσουμε μεταξύ x και y)
    k = len(points[0])  # Διάσταση των σημείων (2 για επίπεδο)
    axis = depth % k  # Επιλέγουμε άξονα με βάση το βάθος

    # Ταξινομούμε τα σημεία κατά τον άξονα που επιλέγουμε
    points.sort(key=lambda x: x[axis])

    # Επιλέγουμε το μεσαίο σημείο ως ρίζα
    median = len(points) // 2
    node = KDTreeNode(points[median])

    # Κατασκευάζουμε αναδρομικά τα αριστερά και δεξιά υποδέντρα
    node.left = build_kd_tree(points[:median], depth + 1)
    node.right = build_kd_tree(points[median + 1:], depth + 1)

    return node

# Οπτικοποίηση του kd-tree
def plot_kd_tree(points, depth=0, ax=None, xmin=-10, xmax=10, ymin=-10, ymax=10):
    if ax is None:
        fig, ax = plt.subplots(figsize=(8, 8))

    if not points:
        return

    k = len(points[0])  # διάσταση (2 για επίπεδο)
    axis = depth % k  # Επιλογή άξονα
    points.sort(key=lambda x: x[axis])

    median = len(points) // 2
    median_point = points[median]

    if axis == 0:  # x-άξονας
        ax.plot([median_point[0], median_point[0]], [ymin, ymax], 'r--')
    else:  # y-άξονας
        ax.plot([xmin, xmax], [median_point[1], median_point[1]], 'b--')

    ax.scatter(*zip(*points), c='black', marker='o')

    plot_kd_tree(points[:median], depth + 1, ax, xmin, xmax, ymin, ymax)
    plot_kd_tree(points[median + 1:], depth + 1, ax, xmin, xmax, ymin, ymax)

    return ax

# Συνάρτηση για την αναζήτηση ορθογώνιας περιοχής
def orthogonal_range_search(node, query_range, depth=0):
    if node is None:
        return []

    x_min, x_max, y_min, y_max = query_range

    # Έλεγχος αν το σημείο του κόμβου βρίσκεται εντός της περιοχής
    x, y = node.point
    result = []
    if x_min <= x <= x_max and y_min <= y <= y_max:
        result.append(node.point)

    # Ανάλογα με τον άξονα (x ή y), αποφασίζουμε ποιο υποδέντρο να εξετάσουμε
    k = len(node.point)
    axis = depth % k

    # Έλεγχος αν πρέπει να αναζητήσουμε στο αριστερό ή δεξί υποδέντρο
    if axis == 0:  # Άξονας x
        if x_min <= x:
            result.extend(orthogonal_range_search(node.left, query_range, depth + 1))
        if x <= x_max:
            result.extend(orthogonal_range_search(node.right, query_range, depth + 1))
    else:  # Άξονας y
        if y_min <= y:
            result.extend(orthogonal_range_search(node.left, query_range, depth + 1))
        if y <= y_max:
            result.extend(orthogonal_range_search(node.right, query_range, depth + 1))

    return result

# Παράδειγμα χρήσης και οπτικοποίησης

# Δημιουργία τυχαίων σημείων
np.random.seed(42)
points = [(np.random.uniform(-10, 10), np.random.uniform(-10, 10)) for _ in range(7)]

# Κατασκευή του kd-tree
kd_tree = build_kd_tree(points)

# Οπτικοποίηση της κατασκευής του kd-tree
ax = plot_kd_tree(points)
plt.title("Οπτικοποίηση του kd-tree")
plt.show()

# Ερώτημα για ορθογώνια περιοχή (x_min, x_max, y_min, y_max)
query_range = (4, 15, 5, 20)
result_points = orthogonal_range_search(kd_tree, query_range)

print("Τα σημεία που βρίσκονται εντός της περιοχής:", result_points)

# Εργασία με 150 σημεία για ορθογώνια αναζήτηση

# Δημιουργία 150 τυχαίων σημείων
points_150 = [(np.random.uniform(-10, 10), np.random.uniform(-10, 10)) for _ in range(150)]

# Κατασκευή του kd-tree για τα 150 σημεία
kd_tree_150 = build_kd_tree(points_150)

# Ορισμός ορθογώνιας περιοχής
query_range_150 = (1, 5, 2, 8)  # x_min, x_max, y_min, y_max
result_points_150 = orthogonal_range_search(kd_tree_150, query_range_150)

# Εκτύπωση αποτελεσμάτων για 150 σημεία
print(f"\nΤα σημεία που βρίσκονται εντός της ορθογώνιας περιοχής {query_range_150}:")
for point in result_points_150:
    print(point)
