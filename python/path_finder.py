from graph import *
from render import *
from graphics import *
from map import *
from geom import *

class Pather:
	def __init__(self, m):
		g = Graph((m.get_waypoints()))
		self.walls = m.walls
		self.waypoints = g.vertices
		for i in range(len(g.matrix)):
			for j in range(len(g.matrix[i])):
				if i == j:
					continue
				if feas_distance(g.vertices[i], g.vertices[j], m.walls) == float("inf"):
					g.remove_edge(i, j)

		# uncomment if you want to see the graph of the waypoints
		# win = GraphWin("Waypoint Graph", 600, 600)
		# draw_graph(g, win)
		# win.getMouse()
		# win.close()

		self.costs, self.paths = g.floyd_warshall()

	def path(self, source, tar):
		stop1 = None
		stop2 = None
		# for wall in self.walls:
		# 	print str(wall)
		min_cost = feas_distance(source, tar, self.walls)
		if min_cost != float("inf"):
			print str(source) + " -> " + str(tar)
			return [source, tar]

		for i in range(len(self.waypoints)):
			for j in range(len(self.waypoints)):
				a = self.waypoints[i]
				b = self.waypoints[j]
				cur_cost = feas_distance(source, a, self.walls) + self.costs[i][j] + feas_distance(b, tar, self.walls)
				if cur_cost < min_cost:
					min_cost = cur_cost
					stop1, stop2 = i, j

		if stop1 == None:
			print("No paths found...")
			return None

		# if stop2 == None:
		# 	print str(source) + " -> " + str(stop1) + " -> " + str(tar)
		# 	return [source, stop1, tar]

		print str(source) + " -> " + str(stop1) + " -> " + str(stop2) + " -> " + str(tar)
		return [source] + self.pointify_path(Graph.fw_path(self.paths, stop1, stop2)) + [tar]

	def pointify_path(self, path):
		return map(lambda x: self.waypoints[x], path)


m = Map("../res/pythtest.map")
win = render_map(m, "black")
pthr = Pather(m)

path_points = pthr.path((1, 1), (599, 599))
draw_path(path_points, "green", win)
win.getMouse()
win.close()