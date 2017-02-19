import random;

def BinarySearch(list, point):
    list.sort();
    lenth = len(list);
    l = 0;
    r = len(list) - 1;
    while(l <= r):
        m = int((l + r) / 2);
        temp = list[m];
        if (point > temp):
            l = m + 1;
        elif (point == temp):
            return m;
        elif (point < temp):
            r = m - 1;
    return -1;

def BinarySearchTest(Max):
    count = 0;
    for i in range(0,Max):
        list = [];
        for j in range(0,i):
            list.append(random.randint(-Max / 4, Max / 4))
        list.sort();
        point = random.randint(-25, 25);
        TestIndex = BinarySearch(list, point);
        try:
            RightIndex = list.index(point);
        except:
            if (TestIndex == -1):
                count += 1;
                pass;
            else:
                print(list);
                print('TestIndex = ', TestIndex, 'RightIndex = ', RightIndex)
                print(point, '：no index error\n');
            continue;
        if (TestIndex != -1):
            count += 1;
            pass;
        else:
            print(list);
            print('TestIndex = ', TestIndex, 'RightIndex = ', RightIndex)
            print(point, '：error\n');
    if (count == Max):
        print('allright');
    return count;    

if __name__ == '__main__':
    Max = 100;
    BinarySearchTest(Max);
        