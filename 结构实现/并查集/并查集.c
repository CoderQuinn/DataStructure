#include <stdio.h>
#define MaxN 10001 // 集合的最大元素个数
#define Null -1 // 初始化值为-1

typedef int ElementType; // 默认集合中元素为整数表示
typedef int SetName; // 默认用根结点的下标作为集合名称
typedef ElementType SetType[MaxN]; // 假设集合元素的下标从0开始, SetType为数组表示集合的别名

/*
 * 初始化集合
 * s:集合指针
 # n:集合的个数
 */
void InitSet(SetType s, int n)
{
    int i;
    for (i = 0; i < n; i++)
        s[i] = Null; // 默认集合元素的根都为Null
}

/* 
 * 1.找x的所属集合,返回集合根的下标;
 * 2.若x不属于任何集合或者本身就是根, 返回x的下标
 */
SetName Find(SetType s, ElementType x)
{
    int ret;
    ret = x;
    while (s[ret] > 0)
    {
        ret = s[ret];
    }
    return ret;
}

void Union(SetType s, ElementType x1, ElementType x2)
{
    int root1, root2;
    root1 = Find(s, x1);
    root2 = Find(s, x2);
    /*
     * 1. 若x1,x2都是初始化结点，那么其根为自身下标，执行if语句
     * 2. 若x1是初始化，x1 == root1, s[root1] = -1,而x2有集合，x2的root2的值s[root2]会小于-1,会执行else
     * 3. 若x2是初始化，x2 == root2, s[root2] = -1,而x1有集合，x1的root1的值s[root1]会小于-1,会执行if
     * 4. 两者都有集合，根据s[root1]<=s[root2]的执行if
     * 5. 两者都有集合，根据s[root1]>s[root2]的执行else
     * 总体上看, 1.2.3,也相当于只有一个元素的集合与另一个大于等于它的集合合并;
     */
    if (s[root1] <= s[root2])
    { // 满足1, 3和4的小于等于情况
        s[root1] += s[root2];
        s[root2] = root1;
    }
    else
    { // 满足2和4的大于情况
        s[root2] += s[root1];
        s[root1] = root2;
    }
}

int isConnection(ElementType x1, ElementType x2, SetType s)
{
    int root1, root2;
    int ret;
    ret = 0;
    root1 = Find(s, x1);
    root2 = Find(s, x2);
    if (root1 == root2)
        ret = 1;
    return ret;
}

int numberOfSets(SetType s, int n)
{
    int i, cnt;
    cnt = 0;
    for (i = 1; i <= n; i++)
    {
        if (s[i] < 0)
            cnt++;
    }
    return cnt;
}