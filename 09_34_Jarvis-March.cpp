#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point {
    int x, y;
};

// A global point needed for sorting points with reference to the first point
struct Point p0;

// Function to swap two points
void swap(struct Point *p1, struct Point *p2) {
    struct Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Returns square of distance between p1 and p2
int distSq(struct Point p1, struct Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r)
// 0 --> collinear, 1 --> clockwise, 2 --> counterclockwise
int orientation(struct Point p, struct Point q, struct Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;           // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// A comparison function used by qsort() to sort points
int compare(const void *vp1, const void *vp2) {
    struct Point *p1 = (struct Point *)vp1;
    struct Point *p2 = (struct Point *)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

// Prints convex hull of a set of n points
void convexHull(struct Point points[], int n) {
    // Find the bottom-most point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Place the bottom-most point at first position
    swap(&points[0], &points[min]);

    // Sort n-1 points with respect to the first point
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(struct Point), compare);

    // Create an array to hold hull points
    struct Point hull[n];
    int m = 1; // Count of unique points
    for (int i = 1; i < n; i++) {
        // Keep removing collinear points near p0
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    if (m < 3) {
        printf("Convex hull not possible\n");
        return;
    }

    // Create a stack and push first three points
    struct Point stack[m];
    int top = 2;
    stack[0] = points[0];
    stack[1] = points[1];
    stack[2] = points[2];

    // Process remaining points
    for (int i = 3; i < m; i++) {
        while (orientation(stack[top - 1], stack[top], points[i]) != 2)
            top--;
        stack[++top] = points[i];
    }

    // Print the convex hull
    printf("Points in Convex Hull are:\n");
    for (int i = 0; i <= top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main() {
    // --- Test Input ---
    struct Point points[] = {
        {0, 3}, {2, 2}, {1, 1}, {2, 1},
        {3, 0}, {0, 0}, {3, 3}
    };
    int n = sizeof(points) / sizeof(points[0]);

    convexHull(points, n);

    return 0;
}

