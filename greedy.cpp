#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

//455. Assign Cookies
int findContentChildren(vector<int> &Children, vector<int> &Cookies)
{
    sort(Children.begin(), Children.end());
    sort(Cookies.begin(), Cookies.end());
    int child = 0, cooky = 0;
    while (child < Children.size() && cooky < Cookies.size())
    {
        if (Children[child] <= Cookies[cooky])
            ++child;
        ++cooky;
    }
    return child;
}
void test455()
{
    vector<int> children;
    vector<int> cookies;
    children.push_back(1);
    children.push_back(3);
    cookies.push_back(1);
    cookies.push_back(2);
    cookies.push_back(4);

    int ret_numChildren = findContentChildren(children, cookies);
    cout << "ret_numChildren=" << ret_numChildren << endl;
}

//135.Candy
int CountCandy(vector<int> &Ratings)
{
    int size = Ratings.size();
    vector<int> num(size, 1);
    if (size < 2)
    {
        return size;
    }

    for (int i = 1; i < Ratings.size(); ++i)
    {
        if (Ratings[i] > Ratings[i - 1])
        {
            num[i] = num[i - 1] + 1;
        }
    }
    for (int i = size - 1; i > 0; --i)
    {
        if (Ratings[i] < Ratings[i - 1])
        {
            num[i - 1] = max(num[i - 1], num[i] + 1);
        }
    }
    cout << "每个小孩得到的糖果个数："
         << " ";
    for (vector<int>::iterator it = num.begin(); it != num.end(); it++)
    {
        cout << *it << " ";
    }
    cout << " " << endl;
    int sum = accumulate(num.begin(), num.end(), 0);
    return sum;
}
void test135()
{
    vector<int> ratings;
    ratings.push_back(1);
    ratings.push_back(0);
    ratings.push_back(2);
    int ret_sumCandy = CountCandy(ratings);
    cout << "ret_sumCandy=" << ret_sumCandy << endl;
}

//435.Non-overlapping Intervals
class GreaterEnd
{
public:
    bool operator()(vector<int> a, vector<int> b)
    {
        return a[1] < b[1];
    }
};

int eraseOverlapIntervals(vector<vector<int> > &Intervals)
{
    if (Intervals.empty())
    {
        return 0;
    }
    int n = Intervals.size();
    sort(Intervals.begin(), Intervals.end(), GreaterEnd()); //先将几个区间按区间结尾大小进行增序排序
    int total = 0, prev = Intervals[0][1];
    for (int i = 1; i < n; ++i)
    {
        if (Intervals[i][0] < prev) //区间重合则需要去除的区间的数量+1
        {
            ++total;
        }
        else
        {
            prev = Intervals[i][1]; //区间不重合则让prve变为后一个区间的结尾
        }
    }
    return total;
}
void test435()
{
    vector<vector<int> > intervals;
    vector<int> v1, v2, v3;
    v1.push_back(1);
    v1.push_back(2);
    intervals.push_back(v1);
    v2.push_back(2);
    v2.push_back(4);
    intervals.push_back(v2);
    v3.push_back(1);
    v3.push_back(3);
    intervals.push_back(v3);
    int ret_TotalIntervals = eraseOverlapIntervals(intervals);
    cout << "ret_TotalIntervals=" << ret_TotalIntervals << endl;
}

int main()
{
    //test455();
    //test135();
    //test435();
}