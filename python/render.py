from graphics import *

def label(p, win, name):
	x = p[0]
	y = p[1] - 10
	t = Text(Point(x, y), name)
	t.setFill("blue")
	t.draw(win)

def draw_graph(g, win):
	for i in range(g.v_num):
			v = g.vertices[i]
			p = Circle(Point(v[0], v[1]), 3)
			p.setFill("black")
			p.draw(win)
			for j in range(i):
				if g.has_edge(i, j):
					draw_line(g.vertices[i], g.vertices[j], "black", win)
			(a, b) = v
			label(v, win, str((round(a, 2), round(b, 2))))

def draw_line(p1, p2, color, win):
	l = Line(Point(p1[0], p1[1]), Point(p2[0], p2[1]))
	l.setFill(color)
	l.draw(win)

def draw_path(ps, color, win):
	for i in range(len(ps)-1):
		draw_line(ps[i], ps[i+1], color, win)

def render_map(m, color):
	win = GraphWin(m.name, m.width, m.height)
	for wall in m.walls:
		draw_line(wall[0], wall[1], color, win)
	return win
