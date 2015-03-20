# Geometry Module

from math import hypot, atan2, sin, cos

RAD = 4

# returns the distance between two points represented by 2-tuples
def distance(p1, p2):
	return hypot(p2[0]-p1[0], p2[1]-p1[1])

# returns infinity if two points are obstructed by a wall in walls
# returns distance otherwise
def feas_distance(p1, p2, walls):
	if obstructed(p1, p2, walls):
		return float("inf")
	return distance(p1, p2)

# checks whether there is an intersection between linesegment (p1, p2)
# and any wall in walls
def obstructed(p1, p2, walls):
	for wall in walls:
		if intersect(p1, p2, wall[0], wall[1]):
			# print "Intersect found! - " + str(p1) + " -> " + str(p2) + " over " + str(wall)
			return True
	# print "No intersection! - " + str(p1) + " -> " + str(p2) + " over " + str(walls)
	return False

# checks whether (p1, p2) and (p3, p4) intersect
def intersect(p1, p2, p3, p4):
	# special cases to avoid dividing by zero
	if p1[0] == p2[0]:
		if p3[0] == p4[0]:
			return	p1[0] == p3[0] and\
					max(p1[1], p2[1]) >= min(p3[1], p4[1]) and\
					max(p3[1], p4[1]) >= min(p1[1], p2[1])
		x = p1[0]
		if (min(p3[0], p4[0]) <= x) and (max(p3[0], p4[0]) >= x):
			m, b = line_eq(p3, p4)
			y = m * x + b
			return	y >= min(p1[1], p2[1]) and\
					y <= max(p1[1], p2[1])
		else:
			return False

	if p3[0] == p4[0]:
		x = p3[0]
		if (min(p1[0], p2[0]) <= x) and (max(p1[0], p2[0]) >= x):
			m, b = line_eq(p1, p2)
			y = m * x + b
			return	y >= min(p3[1], p4[1]) and\
					y <= max(p3[1], p4[1])
		else:
			return False
	# end of special cases

	m1, b1 = line_eq(p1, p2)
	m2, b2 = line_eq(p3, p4)

	# if they're parallel the lines are the same or don't intersect
	if m1 == m2:
		return b1 == b2

	x, y = poi(m1, b1, m2, b2)

	# print("Extended point of intersection: (" + str(x) + ", " + str(y) +  ")")

	return	x <= max(p1[0], p2[0]) and\
			x <= max(p3[0], p4[0]) and\
			x >= min(p1[0], p2[0]) and\
			x >= min(p3[0], p4[0]) and\
			y <= max(p1[1], p2[1]) and\
			y <= max(p3[1], p4[1]) and\
			y >= min(p1[1], p2[1]) and\
			y >= min(p3[1], p4[1])

# finds y-intercept form of line determined by p1 and p2
def line_eq(p1, p2):
	m = (p2[1]-p1[1])/(p2[0]-p1[0])
	b = p1[1]-m*p1[0]
	return m, b

# finds the point of intersection from two point-slope equations
def poi(m1, b1, m2, b2):
	x = (b2 - b1)/(m1-m2)
	return x, m1 * x + b1

# returns a line segment extended by distance RAD
def extend(segment):
	((x1, y1), (x2, y2)) = segment
	ang = atan2(y2-y1, x2-x1)
	xpad = cos(ang) * RAD
	ypad = sin(ang) * RAD
	return ((x1 - xpad, y1 - ypad), (x2 + xpad, y2 + ypad))

