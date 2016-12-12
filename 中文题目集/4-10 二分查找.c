Position BinarySearch( List Tbl, ElementType K )
{
    int left, right;
    left = 0;
    right = Tbl->Last;
    while (left <= right)
    {
        Position mid = (left+right)/2;
        if (Tbl->Data[mid] == K)
            return mid;
        else if(Tbl->Data[mid] > K)
            right = mid-1;
        else
            left = mid+1;
    }
    return NotFound;
}

Position BinarySearch(List l, ElementType x, Position left, Position right)
{
    if (left <= right)
    {
        Position mid = (left+right)/2;
        if (l[mid] == x)
            return mid;
        else if(l[mid] > x)
            return BinarySearch(l, x, left, mid-1);
        else
            return BinarySearch(l, x, mid+1, right);
    }
    else
        return NotFound;
}