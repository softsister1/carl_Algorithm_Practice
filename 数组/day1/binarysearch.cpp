#include <iostream>
#include <vector>
using namespace std;

class Solution
{
    public:
    int search(vector<int>& nums, int target);
};

int Solution::search(vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    int middle = 0;
    while(left <= right)
    {
        middle = (left + right)/2;

        if(nums[middle]>target)
        {
            right = middle - 1;
        }
        else if(nums[middle]<target)
        {
            left = middle;
        }
        else
        return middle;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    Solution a;
    int n = 0;
    cin >> n;
    vector<int> nums(n);
    for (size_t i = 0; i < n; i++)
    {
        /* code */
        cin >> nums[i];
    }
    int target = 0;
    cin >> target;
    int results = a.search(nums, target);

    cout << results << endl;
}
