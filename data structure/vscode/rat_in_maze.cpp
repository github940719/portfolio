#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;


struct Point {
    int x, y ;
    bool valid(bool** maze, int sizeX, int sizeY) {
        return (x >= 0 && y >= 0 && x < sizeX && y < sizeY && maze[x][y] == 0) ;
    }

    bool operator==(const Point& another) {
        return (this->x == another.x && this->y == another.y) ;
    }


    Point operator+ (const Point& another) {
        Point p ;
        p.x = this->x + another.x ;
        p.y = this->y + another.y ;
        return p ;
    }

    void operator=(const Point& another) {
        this->x = another.x ;
        this->y = another.y ;
    }
} ;

// 8 moving directions
Point direction[8] = {
    {0, 1},    // right
    {1, 1},    // right down
    {1, 0},    // down
    {1, -1},   // left down
    {0, -1},   // left
    {-1, -1},  // left up
    {-1, 0},   // up
    {-1, 1},   // right up
};


// stack definition
class myStack {
    private:
        int maxSize ;
        Point* arr = nullptr ;
        int top = -1 ;
    
    public:
        myStack(int maxSize) : maxSize(maxSize) {
            arr = new Point[maxSize] ;
        } 

        ~myStack() {
            delete [] arr ;
            arr = nullptr ;
        }
    
        bool isFull() {
            return (top == maxSize - 1) ;
        }
    
    
        bool isEmpty() {
            return (top == -1) ;
        }
    
        void push(Point element) {
            if (isFull()) {
                throw runtime_error("Stack is full");
            }
            arr[++top] = element ;
        }
    
        Point peek() {
            if (isEmpty()) {
                throw runtime_error("Stack is empty");
            }
            return arr[top] ;
        }
    
        Point pop() {
            if (isEmpty()) {
                throw runtime_error("Stack is empty");
            }
            return arr[top--] ;
        }
    } ;


// main functiob
Point** solveMaze(bool** maze, int sizeX, int sizeY, Point start, Point end) {
    // initialize predecessor = {-1, -1}
    Point** predecessor = new Point*[sizeX] ;
    for (int i = 0; i < sizeX; i++) {
        predecessor[i] = new Point[sizeY] ;
        for (int j = 0; j < sizeY; j++) {
            predecessor[i][j] = {-1, -1} ;
        }      
    }

    myStack toExplore(max(sizeX / 2 * (sizeY + 1), sizeY / 2 * (sizeX + 1))) ;
    toExplore.push(start) ;
    predecessor[start.x][start.y] = start ;

    bool foundPath = false ;
    while (!toExplore.isEmpty()) {
        Point position = toExplore.pop() ;
        if (position == end) {  // find a path
            foundPath = true ;
            break ;
        }

        for (int d = 0; d < 8; d++) {  // for each direction
            Point next = position + direction[d] ;
            if (next.valid(maze, sizeX, sizeY) && (predecessor[next.x][next.y] == Point({-1, -1}))) {  
                toExplore.push(next) ;  // only try valid  and unvisited directions
                predecessor[next.x][next.y] = position ;  // record the predecessor
            }
        }
    }

    return predecessor ;
}


void printPath(Point** predecessor, Point start, Point end, int sizeX, int sizeY) {
    if (predecessor[end.x][end.y] == Point{-1, -1}) {
        cout << "No path found!" << endl ;
        return ;
    }

    // back track the path
    Point current = end ;
    myStack pathStack(max(sizeX / 2 * (sizeY + 1), sizeY / 2 * (sizeX + 1))) ;
    while (!(current == start)) {
        pathStack.push(current) ;
        current = predecessor[current.x][current.y] ;
    }
    pathStack.push(start) ;

    while (!pathStack.isEmpty()) {
        Point p = pathStack.pop() ;
        cout << "(" << p.x << ", " << p.y << ")" ;
        if (!pathStack.isEmpty()) {
            cout << " -> " ;
        }
    }
    cout << endl ;
}


int main() {

    // input
    ifstream file("maze.txt") ;
    Point start, end ;
    int sizeX, sizeY, startX, startY, endX, endY ;
    file >> sizeX >> sizeY >> start.x >> start.y >> end.x >> end.y ;

    // initialize the maze
    bool** maze = new bool*[sizeX] ;  // 0 -> valid, 1 -> wall
    for (int i = 0; i < sizeX; i++) {
        maze[i] = new bool[sizeY] ;
        for (int j = 0; j < sizeY; j++) {
            file >> maze[i][j] ;
        }
    }

    // main function
    Point** path = solveMaze(maze, sizeX, sizeY, start, end) ;
    printPath(path, start, end, sizeX, sizeY) ;
    return 0 ;
}