/* Line segment intersection is a fundamental problem in computational geometry, 
which involves determining whether two line segments intersect and, if so, finding 
the point of intersection. */

/* 
A. Simple Check for Two Segments
    1. Orientation Test:
        - Calculate the orientations for four triplets:
            orientation(p1,q1,p2)
            orientation(p1,q1,q2)
            orientation(p2,q2,p1)
            orientation(p2,q2,q1)
    2. General Case:
        - Two segments (p1, q1) and (p2, q2) intersect if
            orientation(p1,q1,p2) and orientation(p1,q1,q2) are different, and
            orientation(p2,q2,p1) and orientation(p2,q2,q1) are different.
    3. Special Case:
        - Collinear points: Check if the segments overlap.
*/

#include <iostream>
using namespace std;

// Define a Point structure
struct Point {
    int x, y;
};

// Function to determine the orientation of the ordered triplet (p, q, r).
// The function returns:
// 0 if p, q, and r are collinear
// 1 if Clockwise
// 2 if Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2;  // clockwise or counterclockwise
}

// Function to check if point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

// Function to check if line segment 'p1q1' and 'p2q2' intersect
bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    // Find the four orientations needed for the general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1, and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1, and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2, and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2, and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    // Otherwise, the segments do not intersect
    return false;
}

int main() {
    Point p1 = {1, 1}, q1 = {10, 1};
    Point p2 = {1, 2}, q2 = {10, 2};

    if (doIntersect(p1, q1, p2, q2))
        cout << "Yes\n";
    else
        cout << "No\n";

    p1 = {10, 0}, q1 = {0, 10};
    p2 = {0, 0}, q2 = {10, 10};

    if (doIntersect(p1, q1, p2, q2))
        cout << "Yes\n";
    else
        cout << "No\n";

    return 0;
}

