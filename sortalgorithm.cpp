#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//QuickSort快速排序
void QuickSort(vector<int>& nums, int l, int r)
{
    if (l+1>=r)
    {
        return;
    }
    int first = l, last = r-1, key = nums[first];
    while (first < last)
    {
        while (first < last && nums[last] >= key)  // 符合后面数的比key大则将范围向前缩小
        {
            --last;
        }
        nums[first] = nums[last];  // 直到不符合后面数的比key大，则把现在所指向的数nums[last]往前放
        while (first < last && nums[first] <= key) //  符合前面的数比key大则将范围向后缩小
        {
            ++first;
        }
        nums[last] = nums[first]; // 直到不符合前面的数比key小，则把现在所指向的数nums[first]往后放
    }
    nums[first] = key;  // 此时first的位置，左边全部小于key，右边全部大于key  ，把key放在这个位置
    QuickSort(nums,l,first); // 继续排前半部分
    QuickSort(nums,first+1,r); //继续排后半部分  
}


//MergeSort归并排序
void MergeSort1(vector<int>& nums, int l, int r, vector<int>& temp)
{
    if (l+1>=r)
    {
        return;
    }
    //divide
    int m = (l+r)/2;
    MergeSort1(nums, l, m, temp);
    MergeSort1(nums, m, r, temp);
    //conquer
    int p = l, q = m, i = l;
    while (p<m || q<r)
    {  
        if (q >= r || (p < m && nums[p] <= nums[q]))
        {
            temp[i++] = nums[p++];               
        }
        else
        {
            temp[i++] = nums[q++];
        }
    }   
    for (i = l; i < r; ++i)
    {
        nums[i] = temp[i];
    }   
}



//InsertionSort插入排序
void InsertSort(vector<int>& nums, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = i; j > 0 && nums[j] < nums[j-1]; --j)    //j左边是排好序的，j是当前待排序的(插入到前面)，j后面是未拍好序的
        {
            swap(nums[j],nums[j-1]);
        }
        
    }
    
}

//BubbleSort冒泡排序
void BubbleSort(vector<int>& nums, int size)
{
    bool swapped; //记录是否存在交换
    for (int i = 1; i < size; ++i)
    {
        swapped = false;
        for (int j = 1; j < size - i +1; ++j)
        {
            if (nums[j]<nums[j-1])
            {
                swap(nums[j],nums[j-1]);
                swapped = true;
            }    
        }
        if (!swapped)  //如果这轮不存在交换，则退出循环
        {
            break;
        }   
    }
}

//SelectionSort选择排序
void SelctionSort(vector<int>& nums, int size)
{
    int mid;
    for (int i = 0; i < size-1; ++i)
    {
        mid = i;
        for (int j = i+1; j < size; ++j)
        {
            if (nums[j]<nums[mid])
            {
                mid = j;
            }   
        }
        swap(nums[i],nums[mid]);    // 选择这一轮里最小的 放在最前面    
    }   
}
void test_Sort()
{
    vector<int> Nums;
    Nums.push_back(5);
    Nums.push_back(9);
    Nums.push_back(1);
    Nums.push_back(3);
    Nums.push_back(2);
    Nums.push_back(5);
    Nums.push_back(7);
    Nums.push_back(8);
    Nums.push_back(4);
    vector<int> Temp(Nums.size());
    //QuickSort(Nums,0,Nums.size());
    MergeSort1(Nums,0,Nums.size(),Temp);  //？？ 没有理解conquer判断部分
    //InsertSort(Nums,Nums.size());
    //BubbleSort(Nums,Nums.size());
    //SelctionSort(Nums,Nums.size());
    cout<<"ret_NumSort = ";
    for (vector<int>::iterator it = Nums.begin(); it != Nums.end(); ++it)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

// 215. Kth Largest Element in an Array 快速选择————求第k大的数字
int QuickSelectionSort(vector<int>& nums, int l, int r)
{
    int i = l+1, j = r;
    while (true)
    {
        while (i<r && nums[i]<=nums[l])  // 以nums[l]为基准，如果待判断的数小于基准，则可继续判断下一个++i
        {
            ++i;
        }
        while (j>l && nums[j]>=nums[l]) // 以nums[l]为基准，如果待判断的数大于基准，则可继续判断下一个--j
        {
            --j;
        }
        if (i>=j) //此时 退出while循环，让l指向的值和j指向的值互换，因为j如果不等于l的话，j指向的值是小于基准值的
        {
            break;
        }
        // 此时 j所指向的数字小于基准，i所指向的数字大于基准，而i<j,所以让i，j指向的值互换  继续循环
        swap(nums[i],nums[j]);   
    }
    swap(nums[l],nums[j]);
    return j;  //排到位的数是第j小的数  
}
int FindKthLargetst(vector<int>& nums, int k)
{
    int l = 0, r = nums.size()-1, target = nums.size() - k;
    while (l < r)
    {
        int mid = QuickSelectionSort(nums,l,r);
        if (mid == target)
        {
            return nums[mid];
        }
        else if (mid < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }   
    }
    return nums[l];
}
void test215()
{
    vector<int> Nums;
    Nums.push_back(3);
    Nums.push_back(2);
    Nums.push_back(1);
    Nums.push_back(5);
    Nums.push_back(6);
    Nums.push_back(4);
    int k = 2;
    int Kth = FindKthLargetst(Nums, k);
    cout<<"ret_Kth= "<<Kth<<endl;
}

// 347.Top K Freauent Elements 桶排序————求前k个最频繁的数字 （桶统计一个数字出现多少次）
vector<int> TopKthFregent(vector<int> nums, int k)
{
    unordered_map<int,int> counts;
    int max_count = 0;
    for (const int& num:nums)
    {
        max_count = max(max_count,++counts[num]);  // counts统计每个元素出现的次数 max_count得到出现次数最多的数字出现的次数
    }
    vector< vector<int> > buckets(max_count+1);  // 统计出现次数分别为0，1，2...,max_count次的数（一共max_count+1种）
    for (const auto& p:counts)
    {
        buckets[p.second].push_back(p.first);
    }
    vector<int> ret;
    for (int i = max_count; i > 0 && ret.size()<k; --i)
    {
        for(const int & num : buckets[i])
        {
            ret.push_back(num);
            if (ret.size()==k)  // 有可能会出现N个数字出现频次一样，但K=N-M的情况，这时候如果继续push_back,会导致输出结果中num的个数大于k个
            {
                break;
            }
            
        }
    }
    return ret;  
}
void test347()
{
    vector<int> Nums;
    Nums.push_back(3);
    Nums.push_back(3);
    Nums.push_back(3);
    Nums.push_back(5);
    Nums.push_back(6);
    Nums.push_back(4);
    Nums.push_back(6);
    Nums.push_back(9);
    Nums.push_back(1);
    Nums.push_back(2);
    Nums.push_back(4);
    Nums.push_back(4);
    vector<int> ret_topKth = TopKthFregent(Nums,2);
    cout<<"ret_topKth = ";
    for(vector<int>::iterator it = ret_topKth.begin(); it != ret_topKth.end(); ++it)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main()
{
    //test_Sort();
    //test215();
    test347();


}