# 代码随想录算法训练营第一天 | 数组part01

## 今日任务
- 数组理论基础
- 704. 二分查找
- 27. 移除元素
- 977. 有序数组的平方

## 学习资源
- 文章链接：[数组理论基础](https://programmercarl.com/数组理论基础.html)
- 视频讲解：[二分查找](https://www.bilibili.com/video/BV1fA4y1o715)

## 数组理论基础

### 数组定义
数组是存放在连续内存空间上的相同类型数据的集合。

### 重要特点
1. **下标从0开始**
2. **内存空间连续**，这是数组的重要特性
3. **元素类型相同**

### 内存分布
```
数组：[1, 2, 3, 4]
内存：[地址1000][地址1004][地址1008][地址1012]
```

### C++中的数组
```cpp
// 静态数组
int arr[10];

// 动态数组 vector
vector<int> nums;
nums.size();  // 获取长度
```

## 704. 二分查找

### 题目描述
给定一个n个元素有序的（升序）整型数组nums和一个目标值target，写一个函数搜索nums中的target，如果target存在返回下标，否则返回-1。

### 解题关键
- **前提条件**：数组有序
- **时间复杂度要求**：O(log n)
- **核心思想**：每次查找都能排除一半的搜索空间

### 两种写法对比

#### 左闭右闭区间 [left, right]
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;  // 右边界能取到
        
        while (left <= right) {       // 可以相等
            int middle = left + (right - left) / 2;  // 防止溢出
            
            if (nums[middle] > target) {
                right = middle - 1;   // 右边界要-1
            }
            else if (nums[middle] < target) {
                left = middle + 1;
            }
            else {
                return middle;
            }
        }
        return -1;
    }
};
```

#### 左闭右开区间 [left, right)
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size();      // 右边界取不到
        
        while (left < right) {        // 不能相等
            int middle = left + (right - left) / 2;
            
            if (nums[middle] > target) {
                right = middle;       // 右边界不用-1
            }
            else if (nums[middle] < target) {
                left = middle + 1;
            }
            else {
                return middle;
            }
        }
        return -1;
    }
};
```

### 重要细节
1. **防止整数溢出**：使用 `left + (right - left) / 2` 而不是 `(left + right) / 2`
2. **区间定义要一致**：选择一种区间定义并保持一致
3. **边界处理**：左闭右闭时用 `<=`，左闭右开时用 `<`

## 27. 移除元素

### 题目描述
给你一个数组nums和一个值val，你需要原地移除所有数值等于val的元素。返回移除后数组的新长度。

### 解题思路

#### 暴力解法 O(n²)
发现要移除的元素，就将后面的元素都向前移动一位。

#### 双指针法 O(n) ⭐
```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;  // 慢指针：记录下一个保留元素的位置
        
        for (int fast = 0; fast < nums.size(); fast++) {  // 快指针：遍历数组
            if (nums[fast] != val) {
                nums[slow] = nums[fast];  // 保留元素
                slow++;
            }
            // 如果 nums[fast] == val，只移动fast指针
        }
        return slow;  // slow就是新数组的长度
    }
};
```

### 双指针核心思想
- **快指针**：遍历原数组，寻找有效元素
- **慢指针**：指向下一个有效元素应该存放的位置
- **时间复杂度**：O(n)，一次遍历
- **空间复杂度**：O(1)，原地操作

### 算法执行过程
```
数组: [0,1,2,2,3,0,4,2]  val=2

fast=0: nums[0]=0≠2 → nums[0]=0, slow++ → slow=1
fast=1: nums[1]=1≠2 → nums[1]=1, slow++ → slow=2  
fast=2: nums[2]=2=2 → 跳过，slow不变
fast=3: nums[3]=2=2 → 跳过，slow不变
fast=4: nums[4]=3≠2 → nums[2]=3, slow++ → slow=3
fast=5: nums[5]=0≠2 → nums[3]=0, slow++ → slow=4
fast=6: nums[6]=4≠2 → nums[4]=4, slow++ → slow=5
fast=7: nums[7]=2=2 → 跳过，slow不变

结果: [0,1,3,0,4,_,_,_] 返回5
```

## 977. 有序数组的平方

### 题目描述
给你一个按非递减顺序排序的整数数组nums，返回每个数字的平方组成的新数组，要求也按非递减顺序排序。

### 解题思路

#### 暴力解法 O(n log n)
每个元素平方后，再排序。

#### 双指针法 O(n) ⭐
**关键观察**：有序数组平方后，最大值一定出现在两端！

```cpp
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        int left = 0, right = n - 1;
        int pos = n - 1;  // 从结果数组末尾开始填充
        
        while (left <= right) {
            int leftSquare = nums[left] * nums[left];
            int rightSquare = nums[right] * nums[right];
            
            if (leftSquare >= rightSquare) {
                result[pos] = leftSquare;
                left++;
            } else {
                result[pos] = rightSquare;
                right--;
            }
            pos--;
        }
        return result;
    }
};
```

### 算法核心思想
1. **比较两端元素的平方值**
2. **较大的放入结果数组末尾**
3. **从后向前填充结果数组**
4. **移动对应指针**

### 执行过程示例
```
原数组: [-4,-1,0,3,10]
left=0, right=4, pos=4

步骤1: |-4|²=16, |10|²=100, 100更大
       result[4]=100, right--, pos-- → result=[_,_,_,_,100]

步骤2: |-4|²=16, |3|²=9, 16更大  
       result[3]=16, left++, pos-- → result=[_,_,_,16,100]

步骤3: |-1|²=1, |3|²=9, 9更大
       result[2]=9, right--, pos-- → result=[_,_,9,16,100]

步骤4: |-1|²=1, |0|²=0, 1更大
       result[1]=1, left++, pos-- → result=[_,1,9,16,100]

步骤5: |0|²=0
       result[0]=0 → result=[0,1,9,16,100] ✅
```

## 拓展：189. 轮转数组

### 题目描述
给定一个整数数组nums，将数组中的元素向右轮转k个位置。

### 额外空间解法 O(n)
```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> result(n);
        
        for (int i = 0; i < n; i++) {
            result[(i + k) % n] = nums[i];  // 轮转核心公式
        }
        
        for (int i = 0; i < n; i++) {
            nums[i] = result[i];
        }
    }
};
```

### 核心公式
`nums[i]` 向右移动k步后的新位置：`(i + k) % n`

## 学习总结

### 今日收获
1. **掌握了二分查找的两种区间写法**，理解了区间定义的重要性
2. **学会了双指针技巧**，能够用O(n)时间复杂度解决数组问题
3. **理解了有序数组的特性**，学会利用有序性优化算法
4. **掌握了时间复杂度分析**，能够从暴力解法优化到最优解法

### 双指针适用场景
- **有序数组问题**：利用两端的特殊性
- **原地操作问题**：用快慢指针避免额外空间
- **配对查找问题**：从两端向中间逼近

### 时间复杂度优化思路
1. **看数据特征**：有序→二分查找/双指针
2. **看操作特征**：查找→二分/哈希，配对→双指针
3. **避免嵌套循环**：用双指针实现一次遍历

### 学习时长
今日学习时长：4小时
- 理论学习：1小时
- 编程实践：2小时  
- 总结整理：1小时

### 遇到的困难
1. **初始对sizeof的误用**：学会了vector要用.size()而不是sizeof
2. **二分查找边界处理**：通过对比两种区间写法加深理解
3. **双指针思维转换**：从暴力解法到双指针需要思维转变



