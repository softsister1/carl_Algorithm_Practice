#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>>Matrix(n, vector<int>(n, 0));
        int row = 0, col = 0;  // 当前位置
        int direction = 0;     // 0:右, 1:下, 2:左, 3:上
        // 四个方向的行、列变化
        int dr[] = {0, 1, 0, -1};  // 行变化：右0下+1左0上-1
        int dc[] = {1, 0, -1, 0};  // 列变化：右+1下0左-1上0
        for (int i = 1; i <= n * n; i++) {
            matrix[row][col] = i;  // 填入当前数字
            
            // 计算下一个位置
            int nextRow = row + dr[direction];
            int nextCol = col + dc[direction];
            
            // 判断是否需要转向
            if (row == n || col == n || matrix[row + 1][col] > 0 || matrix[row][col + 1] > 0 ) {
                direction = (direction + 1) % 4;  // 顺时针转向
                nextRow = row + dr[direction];
                nextCol = col + dc[direction];
            }
            
            // 移动到下一个位置
            row = nextRow;
            col = nextCol;
        }
    }
};