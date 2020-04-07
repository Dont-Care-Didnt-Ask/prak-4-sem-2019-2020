int main()
{
    int count;
    std::cin >> count;

    Holder *arr = new Holder[count];
    for (int i = 0; i < count/2; i++){
        arr[i].swap(arr[count - 1- i]);
    }
    delete [] arr;
    return 0;
}

/*
though

for (int i=0; i < count; i++) {
    Holder tmp;
}

should be able to get the job done
*/