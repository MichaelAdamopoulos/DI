import numpy as np
import random
import matplotlib.pyplot as plt
from scipy.spatial import Delaunay, Voronoi, voronoi_plot_2d

# Generate random points
n = 15
points = np.array([(random.randint(0, 100), random.randint(0, 100)) for _ in range(n)])

# Delaunay triangulation
triangulation = Delaunay(points)

# Voronoi diagram
voronoi = Voronoi(points)

plt.figure(figsize=(15, 5))

# Plot Delaunay
plt.subplot(131)
plt.triplot(points[:, 0], points[:, 1], triangulation.simplices, color='b')
plt.plot(points[:, 0], points[:, 1], 'ro')
plt.title('Delaunay')

# Plot Voronoi
plt.subplot(132)
voronoi_plot_2d(voronoi, ax=plt.gca(), show_vertices=False, line_colors='r')
plt.plot(points[:, 0], points[:, 1], 'ro')
plt.title('Voronoi')

# Plot both Delaunay and Voronoi
plt.subplot(133)
voronoi_plot_2d(voronoi, ax=plt.gca(), show_vertices=False, line_colors='r')
plt.triplot(points[:, 0], points[:, 1], triangulation.simplices, color='b')
plt.plot(points[:, 0], points[:, 1], 'ro')
plt.title('Delaunay + Voronoi')

# Show the plots
plt.tight_layout()
plt.show()
