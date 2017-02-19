def ReversalList(list):
    l = 0;
    r = len(list) - 1;
    while(l < r):
        list[l], list[r] = list[r], list[l];
        l += 1;
        r -= 1;
    return list;

def LeftReverseList(list, n):
    LeftList = ReversalList(list[0 : n]);
    RightList = ReversalList(list[n : len(list)]);
    return ReversalList(LeftList + RightList);

def LeftReverseListTest(Max):
    count = 0;
    for i in range(0,Max):
        list = [];
        for j in range(0,i):
            list.append(random.randint(-int(Max / 2), int(Max / 2)));
        test = random.randint(0, i);
        NewList = LeftReverseList(list, test);
        print(test);
        print(list);
        print(NewList);
        if (list != LeftReverseList(NewList, i - test)):
            print(list);
            print(i, '£ºerror\n');
        else:
            count += 1;
    if (count == Max):
        print('allright');
    return count;


if __name__ == '__main__':
    Max = 10;
    LeftReverseListTest(Max);