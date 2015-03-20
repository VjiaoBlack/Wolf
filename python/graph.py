from geom import *
from graphics import *

class Graph:
	def __init__(self, pointlist):
		self.v_num = len(pointlist)
		self.matrix = [[] for x in range(self.v_num)]
		self.vertices = pointlist
		for i in range(self.v_num):
			self.matrix[i] = [float("inf") for j in range(0, i+1)]
		for i in range(self.v_num):
			for j in range(i+1):
				self.matrix[i][j] = distance(pointlist[i], pointlist[j])

	def __str__(self):
		string = ""
		for i in range(self.v_num):
			for j in range(i+1):
				string += str(round(self.matrix[i][j], 2)) + ",\t"
			string += "\n"
		return string

	@staticmethod
	def al_to_string(adj):
		string = ""
		for i in range(len(adj)):
			string += str(i) + ": "
			for j in range(len(adj[i])):
				string += "(" + str(adj[i][j][0]) + ", " \
						+ str(round(adj[i][j][1], 2)) + ")" + ",\t"
			string += "\n"
		return string

	@staticmethod
	def fl_to_string(fl):
		string = ""
		for i in range(len(fl)):
			for j in range(len(fl[i])):
				string += str(round(fl[i][j],2)) + ",\t"
			string += "\n"
		return string


	def get_vertex(self, v):
		return self.vertices[v]
		
	def add_edge(self, v1, v2, weight):
		if v2 > v1:
			v1, v2 = v2, v1
		self.matrix[v1][v2] = weight
	
	def has_edge(self, v1, v2):
		if v2 > v1:
			v1, v2 = v2, v1
		if v1 >= len(self.matrix):
			print "First index out of bounds: " + str(v1) + " >= " + str(len(self.matrix))
			return False
		if v2 >= len(self.matrix[v1]):
			print "Second index out of bounds: " + str(v2) + " >= "+ str(len(self.matrix[v1]))
			return False
		return self.matrix[v1][v2] != float("inf")

	def remove_edge(self, v1, v2):
		if v2 > v1:
			v1, v2 = v2, v1
		if not self.has_edge(v1, v2):
			"No edge to remove!"
		self.matrix[v1][v2] = float("inf")

	def adjlist(self):
		adj = [[] for x in range(self.v_num)]
		for i in range(self.v_num):
			for j in range(i):
				if self.has_edge(i, j):
					adj[i] += (j, self.matrix[i][j]),
					adj[j] += (i, self.matrix[i][j]),
		return adj

	def edgelist(self):
		edges = []
		for i in range(self.v_num):
			for j in range(i):
				if self.has_edge(i, j):
					edges += (i, j),
					# edges += (j, i),
		return edges

	def al_string(self):
		adj = self.adjlist()
		return Graph.al_to_string(adj)

	def floyd_warshall(self):
		V = self.v_num
		dist = [[float("inf") for x in range(V)] for x in range(V)]
		next = [[None for x in range(V)] for x in range(V)]
		for v in range(V):
			dist[v][v] = 0
			next[v][v] = v
		for (u, v) in self.edgelist():
			if v > u:
				u, v = v, u
			dist[u][v] = self.matrix[u][v]
			dist[v][u] = self.matrix[u][v]
			next[u][v] = v
			next[v][u] = u
		for k in range(V):
			for i in range(V):
				for j in range(V):
					if dist[i][j] > dist[i][k] + dist[k][j]:
						dist[i][j] = dist[i][k] + dist[k][j]
						dist[j][i] = dist[i][k] + dist[k][j]
						next[i][j] = next[i][k]
						next[j][i] = next[j][k]
		return dist, next

	@staticmethod
	def fw_path(next, u, v):
		if next[u][v] == None:
			return []
		path = [u]
		while u != v:
			u = next[u][v]
			path += [u]
		return path
