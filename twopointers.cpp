#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

//167. Two Sum II -Input array is sorted
vector<int> TwoSum1(vector<int> &Numbers, int Target)
{ //方法一：这种考虑不全面，只适用于两个正整数相加
    //先将l指向第一个r指向最后一个 并相加，如果大于目标值则r向前移一位，反之l向后移
    int size = Numbers.size();
    int l = 0, r = size - 1, sum = 0;
    while (l < r)
    {
        sum = Numbers[l] + Numbers[r];
        if (sum == Target)
            break;
        if (sum < Target)
        {
            ++l;
        }
        else
        {
            --r;
        }
    }
    vector<int> ret;
    ret.push_back(l + 1);
    ret.push_back(r + 1);
    return ret;
}
vector<int> TwoSum2(vector<int> &nums, int target)
{ //LeetCode题解
    unordered_map<int, int> hashmap;
    for (int i = 0; i < nums.size(); ++i)
    {
        auto t = hashmap.find(target - nums[i]);
        if (t != hashmap.end())
        {
            return {t->second, i};
        }
        hashmap[nums[i]] = i;
    }
    return { };
}
void test167()
{
    vector<int> numbers;
    numbers.push_back(2);
    numbers.push_back(7);
    numbers.push_back(11);
    numbers.push_back(15);
    vector<int> ret_twoSum = TwoSum2(numbers, 9);
    cout << "ret_twoSum="
         << " ";
    for (vector<int>::iterator it = ret_twoSum.begin(); it != ret_twoSum.end(); it++)
    {
        cout << *it << " ";
    }
    cout << " " << endl;
}

//88. Merge Sorted Arrray
void MergeArray1(vector<int> &Nums1, int M, vector<int> &Nums2, int N)
{
    //判断Nums1和Nums2的最后一个数，把大的放在nums1最后一位
    //我的方法
    int MN = M + N;
    for (int i = MN; i > 0; --i)
    {
        if (Nums1[M - 1] < Nums2[N - 1])
        {
            Nums1[MN - 1] = Nums2[N - 1];
            --N;
        }
        else
        {
            Nums1[MN - 1] = Nums1[M - 1];
            --M;
        }
        --MN;
    }
    //这里不需要写return，因为返回的是nums1指针
}
vector<int> MergeArray2(vector<int> Nums1, int M, vector<int> Nums2, int N)
{
    //题解的方法
    int pos = M-- + N-- - 1; //返回M-1和N-1的值，方便后面使用
    while (M >= 0 && N >= 0)
    {
        Nums1[pos--] = Nums1[M] > Nums2[N] ? Nums1[M--] : Nums2[N--];
    }
    while (N >= 0) //如果Nums2都排完了，此时Nums1的即使没有排完也是按顺序的，无需再考虑M>=0;但如果Nums1都排完了，需要把Nums2的放到Nums1里面
    {
        Nums1[pos--] = Nums2[N--];
    }
}
void test88()
{
    vector<int> nums1;
    vector<int> nums2;
    nums1.push_back(1);
    nums1.push_back(2);
    nums1.push_back(3);
    nums2.push_back(2);
    nums2.push_back(5);
    nums2.push_back(6);
    int m = nums1.size();
    int n = nums2.size();
    int mn = m + n;
    nums1.resize(mn, 0);
    MergeArray1(nums1, m, nums2, n);
    //MergeArray2(nums1, m, nums2, n);
    cout << "ret_merge=";
    for (vector<int>::iterator it = nums1.begin(); it != nums1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << " " << endl;
}

// 链表
// 142. Linked List Cycle II(快慢指针Floyd判圈法)
struct ListNode
{
    int val;                                   //链表的某个值
    ListNode *next;                            //链表指针指向的是下一个元素
    ListNode(int x) : val(x), next(nullptr) {} //初始化当前节点值为x，指针为空；
};
ListNode *detectCycle(ListNode *head)
{
    ListNode *slow = head, *fast = head;
    //当fast和slow相遇时，fast走的路程一定是slow的n*cycle，此时他们所在的位置离cycle起点的距离等于链表起点离cycle起点的距离
    //判断是否存在环路
    do
    {
        /* code */
        if (!fast || !fast->next)
        {
            return nullptr;
        }
        fast = fast->next->next;
        slow = slow->next;
    } while (fast != slow);
    //如果存在，查找环路节点
    fast = head;
    while (fast != slow)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}
void test142()
{
    ListNode *phead = new ListNode(0);
    ListNode *firstnode = new ListNode(1);
    ListNode *secondnode = new ListNode(2);
    ListNode *thirdnode = new ListNode(3);
    phead->val = 3;
    phead->next = firstnode;
    firstnode->val = 2;
    firstnode->next = secondnode;
    secondnode->val = 0;
    secondnode->next = thirdnode;
    thirdnode->val = -4;
    thirdnode->next = firstnode;
    ListNode *ret_node = detectCycle(phead);
    cout << "ret_node= " << ret_node->val << endl;
}

// 滑动窗口
// 76.Minimum Window Substring
string minWindow(string S, string T)
{
    vector<int> chars(128, 0); //128应该是各种字符的总数
    vector<bool> flag(128, true);
    //先统计T中字符串的情况
    for (int i = 0; i < T.size(); ++i)
    {
        flag[T[i]] = true; // flag 表示每个字符是否在T中存在
        ++chars[T[i]];     // chars 表示目前每个字符缺少的数量
    }
    //移动滑动窗口，不断更改统计数据
    int cnt = 0, l = 0, min_l = 0, min_size = S.size() + 1; //滑动窗口必备参数。cnt:窗口中包含的T中字符的个数
    for (int r = 0; r < S.size(); ++r)                      //窗口右边界向右移动
    {
        if (flag[S[r]])
        {
            if (--chars[S[r]] >= 0)
            {
                ++cnt; //需要才加1，不需要则不加：即改变与T的距离
            }
            //若目前滑动窗口已经包含T中全部字符
            //则尝试将l右移，在不影响结果的情况下获取最短子字符串
            while (cnt == T.size())
            {
                if (r - l + 1 < min_size) //调整窗口大小
                {
                    min_l = l;
                    min_size = r - l + 1;
                }
                if (flag[S[l]] && ++chars[S[l]] > 0) //窗口左边向右移动
                {
                    --cnt;
                }
                ++l;
            }
        }
    }
    return min_size > S.size() ? "" : S.substr(min_l, min_size);
}
void test76()
{
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string ret_minstr = minWindow(s, t);
    cout << "ret_minstr=" << ret_minstr << endl;
}

int main()
{
    //test167();  //? auto错误
    //test88();
    //test142();
    //test76();//*(需要加深理解)
}