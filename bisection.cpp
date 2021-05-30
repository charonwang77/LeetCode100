#include <iostream>
#include <vector>

using namespace std;

// 69.Sqrt(x)
int mySqrt1(int a)
{
    //二分法
    if (a == 0)
        return a;
    int l = 0, r = a, mid, sqrt;
    while (l <= r)
    {
        mid = (l + r) / 2;
        sqrt = a / mid;
        if (sqrt == mid)
        {
            return mid;
        }
        else if (sqrt > mid) //说明mid比目标值小了，l向右移
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return r;
}
int mySqrt2(int a)
{
    //牛顿迭代法:Xn+1 = Xn -f(Xn)/f'(Xn)
    //f(x) = x^2 -a = 0  带入上式得到：Xn+1 = (Xn+a/Xn)/2
    long x = a;
    while (x * x > a)
    {
        x = (x + a / x) / 2;
    }
    return x;
}
void test69()
{
    int A = 7;
    int sqrt_A = mySqrt1(A);
    cout << "sqrt_A= " << sqrt_A << endl;
}

// 34.Find First and Last Position of Element in Sorted Array
int LowerBound(vector<int>& nums, int target)
{
    int l = 0, r = nums.size(), mid;
    while (l < r)
    {
        mid = (l+r)/2;
        if (nums[mid] >= target) r = mid;  //一旦等于了，就不能让l去动，而r去动，这样找到的就是
        else l = mid+1;
    }
    return l;
}
int UpperBound(vector<int>& nums, int target)
{
    int l = 0, r = nums.size(), mid;
    while (l < r)
    {
        mid = (l+r)/2;
        if (nums[mid] > target) r = mid;  // 只要是等于，就可以让l右移，这样就能找到最大的位置
        else l = mid+1;
    }
    return l-1;
}
vector<int> SearchRange(vector<int>& nums, int target)
{
    vector<int> inexist;
    inexist.push_back(-1);
    inexist.push_back(-1);
    if(nums.empty()) return inexist;
    int lower = LowerBound(nums,target);
    int upper = UpperBound(nums,target);
    if (lower == nums.size() && nums[lower] != target)
    {
        return inexist;
    }
    vector<int> ret;
    ret.push_back(lower);
    ret.push_back(upper);
    return ret;
}
void test34()
{
    vector<int> Nums;
    Nums.push_back(5);
    Nums.push_back(7);
    Nums.push_back(7);
    Nums.push_back(8);
    Nums.push_back(8);
    Nums.push_back(9);
    int Target = 8;
    vector<int> ret_Range = SearchRange(Nums, Target);
    cout<<"ret_Range= ";
    for (vector<int>::iterator it = ret_Range.begin(); it != ret_Range.end(); ++it)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

// 81. Search in Rotated Sorted Array II
bool SearchCycle(vector<int>& nums, int target)
{
    int start = 0, end = nums.size()-1, mid;
    while (start <= end)
    {
        mid = (start + end)/2;
        //若mid等于target直接返回
        if (nums[mid] == target) return true;      
        //若mid等于start无法判定哪个区间是赠序的，start++
        if (nums[mid] == nums[start]) ++start;
        //若mid右区间是增序的，则判断target在不在其中，并改变区间
        else if (nums[mid]<=nums[end])
        {
            if (target > nums[mid] && target <= nums[end])
            {
                start = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
            
        }
        //若mid左区间是增序的，则判断target在不在其中，并改变区间
        else
        {
            if (target >= nums[start] && target < nums[mid])
            {
                end  = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
            
        }
    }
    return false;
}
void test81()
{
    vector<int> Nums;
    Nums.push_back(2);
    Nums.push_back(5);
    Nums.push_back(6);
    Nums.push_back(0);
    Nums.push_back(0);
    Nums.push_back(0);
    Nums.push_back(1);
    Nums.push_back(2);
    int Target = 4;
    bool ret_SearchCycle = SearchCycle(Nums, Target);
    cout<<"ret_SearchCycle= "<<ret_SearchCycle<<endl;

}

int main()
{
    //test69();
    //test34();
    //test81();
}