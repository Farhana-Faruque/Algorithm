#include <stdio.h>
#include <stdlib.h>

// Define a Point structure
typedef struct {
    int x, y;
} Point;

// Function to find the orientation of the ordered triplet (p, q, r)
// 0 --> collinear, 1 --> Clockwise, 2 --> Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

// Comparison function to sort points by x-coordinate, breaking ties by y-coordinate
int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x == p2->x)
        return p1->y - p2->y;
    return p1->x - p2->x;
}

// Function to compute the convex hull using Graham's Scan algorithm
void convexHull(Point points[], int n) {
    if (n < 3) {
        printf("Convex hull not possible\n");
        return;
    }

    // Step 1: Find the bottom-most point (or leftmost if tie)
    int minYIndex = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minYIndex].y || 
            (points[i].y == points[minYIndex].y && points[i].x < points[minYIndex].x))
            minYIndex = i;
    }

    // Place the lowest point at the beginning
    Point temp = points[0];
    points[0] = points[minYIndex];
    points[minYIndex] = temp;

    // Step 2: Sort remaining points based on polar angle with respect to pivot
    Point pivot = points[0];
    qsort(points + 1, n - 1, sizeof(Point), compare);

    // Step 3: Build the convex hull using an array as a stack
    Point hull[n];
    int hullSize = 0;
    hull[hullSize++] = points[0];
    hull[hullSize++] = points[1];
    hull[hullSize++] = points[2];

    for (int i = 3; i < n; i++) {
        while (hullSize > 1 && orientation(hull[hullSize - 2], hull[hullSize - 1], points[i]) != 2)
            hullSize--; // Remove last point if it makes a clockwise turn
        hull[hullSize++] = points[i];
    }

    // Print the convex hull points
    printf("Convex Hull Points:\n");
    for (int i = 0; i < hullSize; i++)
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
}

// Driver function
int main() {
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);
    convexHull(points, n);
    return 0;
}