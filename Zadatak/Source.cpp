#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>

using namespace std;

const int ROWS = 20;
const int COLS = 40;

struct Point {
    int row;
    int col;

    Point(int r, int c) : row(r), col(c) {}
};

void drawField(const vector<vector<char>>& field) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            putchar(field[i][j]);
            putchar(' ');
        }
        putchar('\n');
    }
    putchar('\n');
}

bool isValid(int row, int col) {
    return (row >= 0 && row < ROWS&& col >= 0 && col < COLS);
}

bool isWall(const vector<vector<char>>& field, int row, int col) {
    return (field[row][col] == '#');
}

vector<Point> findPath(const Point& start, const Point& end, const vector<vector<char>>& field) {
    vector<vector<int>> distance(ROWS, vector<int>(COLS, INT_MAX));
    vector<vector<Point>> parent(ROWS, vector<Point>(COLS, Point(-1, -1)));

    distance[start.row][start.col] = 0;

    queue<Point> q;
    q.push(start);

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.row == end.row && curr.col == end.col) {
            break;
        }

        int dr[] = { -1, 0, 1, 0 };
        int dc[] = { 0, 1, 0, -1 };

        for (int i = 0; i < 4; i++) {
            int newRow = curr.row + dr[i];
            int newCol = curr.col + dc[i];

            if (isValid(newRow, newCol) && !isWall(field, newRow, newCol)) {
                int newDist = distance[curr.row][curr.col] + 1;

                if (newDist < distance[newRow][newCol]) {
                    distance[newRow][newCol] = newDist;
                    parent[newRow][newCol] = curr;
                    q.push(Point(newRow, newCol));
                }
            }
        }
    }

    vector<Point> path;

    if (parent[end.row][end.col].row != -1 && parent[end.row][end.col].col != -1) {
        Point curr = end;
        while (curr.row != start.row || curr.col != start.col) {
            path.push_back(curr);
            curr = parent[curr.row][curr.col];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
    }

    return path;
}

void drawPath(const vector<Point>& path, const vector<vector<char>>& field) {
    vector<vector<char>> tempField = field;

    for (const Point& p : path) {
        tempField[p.row][p.col] = '*';
        drawField(tempField);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    vector<vector<char>> field(ROWS, vector<char>(COLS, '.'));

    field[0][9] = '#';
    field[1][9] = '#';
    field[2][9] = '#';
    field[3][9] = '#';
    field[4][9] = '#';
    field[5][9] = '#';

    field[5][10] = '#';
    field[6][10] = '#';
    field[7][10] = '#';

    field[7][11] = '#';
    field[8][11] = '#';
    field[9][11] = '#';
    field[10][11] = '#';

    field[15][25] = '#';
    field[15][26] = '#';
    field[15][27] = '#';
    field[15][28] = '#';
    field[15][29] = '#';
    field[15][30] = '#';

    int startRow, startCol, endRow, endCol;
    cout << "Unesite redak i stupac pocetne tocke A: ";
    cin >> startRow >> startCol;
    cout << "Unesite redak i stupac krajnje tocke B: ";
    cin >> endRow >> endCol;

    Point start(startRow - 1, startCol - 1);
    Point end(endRow - 1, endCol - 1);

    vector<Point> path = findPath(start, end, field);

    drawPath(path, field);

    return 0;
}
