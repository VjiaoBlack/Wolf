#include "physics_handler.h"
// int intersect(line *a, line *b);
// int orientation(line *l, vector2 *pt);

int valid_move(vector2 *pos, int x_off, int y_off, world *w) {
	//initialize_terrain(w->w_mesh);
	vector2 *v = new_vector2(pos->x + x_off, pos->y + y_off);
	int b = is_open(v);
	free_vector2(v);
	//free_terrain();
	return b;
} 



// 	line **lines = w->w_mesh->m_lines;
// 	int line_num = w->w_mesh->num_walls;
// 	line *cur = new_line(pos->x, pos->y, pos->x + x_off, pos->y + y_off);

// 	for (int i = 0; i < line_num; ++i)
// 		if (intersect(lines[i], cur)) {
// 			//sleep(10);
// 			return 0;
// 		}

// 	free_line(cur);
// 	return 1;
// }

// int intersect(line *a, line *b) {
// 	vector2 *a1 = a->position1;
// 	vector2 *a2 = a->position2;

// 	vector2 *b1 = a->position1;
// 	vector2 *b2 = a->position2;

// 	int o1 = orientation(a, b1);
// 	printf("Orientation 1: %d\n", o1);
// 	int o2 = orientation(a, b2);
// 	printf("Orientation 2: %d\n", o2);
// 	int o3 = orientation(b, a1);
// 	printf("Orientation 3: %d\n", o3);
// 	int o4 = orientation(b, a2);
// 	printf("Orientation 4: %d\n", o4);

// 	int c1 = o1 != o2;
// 	int c2 = o3 != o4;
// 	// int c3 = o1 == 0;
// 	// int c4 = o3 == 0;

// 	return c1 && c2;

// }


// /*
//  * pt on l -> 0
//  * pt above/left l -> 1
//  * pt bottom/right l -> -1
//  */
// int orientation(line *l, vector2 *pt) {
// 	float x1 = l->position1->x;
// 	float x2 = l->position2->x;
// 	float y1 = l->position1->y;
// 	float y2 = l->position2->y; 

// 	float x = pt->x;
// 	float y = pt->y;

// 	if (x1 == x2) {
// 		if (x > x1) return 1;
// 		if (x < x1) return -1;
// 		return 0;
// 	}
// 	float slope = (y2 - y1)/(x2 - x1);
// 	float above = slope * (x-1) + y1 - y;

// 	if (above > 0) return 1;
// 	if (above < 0) return -1;
// 	return 0;
// }

