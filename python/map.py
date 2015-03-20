from geom import extend

class Map:
	def __init__(self, fylename):
		self.name = fylename

		doc = open(fylename, "r")
		content = doc.read()

		words = content. split()

		self.num_walls, self.width, self.height = int(words[0]), int(words[1]), int(words[2])

		self.walls = []
		for i in range((len(words)-3)/4):
			st = 4 * i + 3
			p1 = (float(words[st]), float(words[st+1]))
			# print p1
			p2 = (float(words[st+2]), float(words[st+3]))
			# print p2
			self.walls.append((p1, p2))

	def get_waypoints(self):
		ps = []
		for wall in self.walls:
			ext = extend(wall)
			ps.append(ext[0])
			ps.append(ext[1])
		return ps