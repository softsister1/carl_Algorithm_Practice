// #include<iostream>
// #include<vector>


// using namespace std;

// int main()
// {
//     int n = 0;
//     cin << n;
//     vector(int) nums(n);

//     for(int i = 0; i < n; i++)
//     {
//         cin << nums[i];
//     }
//     int left = 0;
//     int right = 0;
//     int sum = 0;

//     cin << left,right;
//     for(i = left; i < right; i++)
//     {
//         sum +=nums[i];
//     }
//     cout >> sum;
//     return 0;
// }


#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;  // 修正：使用 >> 而不是 <<
    
    vector<int> nums(n);  // 修正：使用 <> 而不是 ()
    
    // 读取数组元素
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int left, right;
    // 修正：处理多组输入，直到文件结束
    while (cin >> left >> right) {  // 修正：使用 >> 读取两个数
        int sum = 0;
        
        // 修正：循环条件改为 <= ，包含右端点
        for (int i = left; i <= right; i++) {  // 修正：声明变量类型
            sum += nums[i];
        }
        
        cout << sum << endl;  // 修正：使用 << 输出，添加换行
    }
    <<
    return 0;
}

/*
示例验证：
输入：
5
1 2 3 4 5
0 1
1 3

数组：[1, 2, 3, 4, 5]
      索引: 0  1  2  3  4

查询1：区间[0,1] = nums[0] + nums[1] = 1 + 2 = 3 ✓
查询2：区间[1,3] = nums[1] + nums[2] + nums[3] = 2 + 3 + 4 = 9 ✓
*/