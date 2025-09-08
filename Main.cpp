//copy constructor helper
void DoubleList::copyHelper(const DoubleList& rhs)
{
    numDoubles = rhs.numDoubles;
    capacity = rhs.capacity;

    if (rhs.theArray != nullptr)
    {
        theArray = new double[capacity];
        copyArray(theArray,rhs.theArray);
    }
    else
        theArray = nullptr;

    cout<<"copy made"<<endl;
}

//Default copy construct
DoubleList::DoubleList(const DoubleList& rhs)
{
    copyHelper(rhs);
}

//Default assignment operator
DoubleList& DoubleList::operator=(const DoubleList& rhs)
{
    if (this != &rhs)
    {
        delete[] theArray;
        copyHelper(rhs);
    }
    return *this;

}

//Default deconstructor
DoubleList::~DoubleList()
{
    delete[] theArray;
    theArray = nullptr;
    
    cout<<"deconstructed"<<endl;
}

//Adds data to the end of the list
void DoubleList::addDouble(double doubleToAdd)
{
    //allocated space if neccessary
    if (numDoubles == capacity-1)
    {
        allocate();
    }
    
    //adds data
    theArray[numDoubles] = doubleToAdd;
    numDoubles++;

    //system output
    //cout<<"Double added: "<<doubleToAdd<<endl;
}

void DoubleList::allocate()
{
    double* newArray = new double[capacity+10];
    copyArray(newArray,theArray);
    
    delete[] theArray;
    theArray = newArray;
    capacity = capacity+10;

    //cout<<"Allocated room"<<endl;
}

//removes double at the end of the list
void DoubleList::removeDouble()
{
    if (numDoubles == 0)
    {
        cout<<"No doubles left"<<endl;
    }
    else
    {
        numDoubles--;
        theArray[numDoubles] = 0;
        //cout<<"Double removed"<<endl;
    }
}

//swaps the two nodes following prevNode
void swap(Node* prevNode)
{
    //1st element gets put into temp slot and skips the next element
    Node* temp = new Node(prevNode->next->dataVal);
    temp->next = prevNode->next->next->next;
    
    //1st element is replaced by skiped element
    prevNode->next = prevNode->next->next;
    //instert temp node
    prevNode->next->next = temp;
}

void swap(DLNode* prevNode)
{
    //1st elemet gets put in temp slot and skips the next element whie revers pointing to the 2nd element
    DLNode* temp = new DLNode(prevNode->next->dataVal);
    temp->next = prevNode->next->next->next;
    temp->prev = prevNode->next->next;
    //4th element points to temp
    prevNode->next->next->next->prev = temp;

    //2nd element takes 1st element spot
    prevNode->next = prevNode->next->next;
    //2nd element now points to head
    prevNode->next->prev = prevNode;
    //insert 1st element
    prevNode->next->next = temp;
}

// prints the elements from listToPrintFrom at the indices in indexList to the screen. 
// The indices are zero-based. Neither list is modified in any way.
// Preconditions: indexList is sorted in ascending order and the last value in
//                indexList is less than the length of listToPrintFrom
//Big-Oh:O(n)
void printByIndex(Node* listToPrintFrom, Node* indexList)
{
    cout<<" ";

    //make temp lists
    Node* tempIndex = indexList;
    Node* tempList = listToPrintFrom;

    int index = tempIndex->dataVal;

    for (int x = 0; tempIndex != nullptr; x++)
    {   
        if (index == x)
        {
            cout<<tempList->dataVal<<" ";
            if (tempIndex->next != nullptr)
                index = tempIndex->next->dataVal;
            tempIndex=tempIndex->next;
        }
        
        tempList = tempList->next;
    }
    cout<<endl;
}

void doUnion(const list<int>& list1, const list<int>& list2, list<int>& result)
{
    //creates iterators to travse the list
    list<int>::const_iterator iter1 = list1.begin();
    list<int>::const_iterator iter2 = list2.begin();
   
    //adds list 1 and 2 too results sorted
    while (iter1 != list1.end() && iter2 != list2.end())
    {
        //adds list 1 element since its smaller
        if (*iter1 < *iter2)
        {
            result.push_back(*iter1);
            iter1++;
        }
        //adds list 2 element since its smaller
        else if (*iter2 < *iter1)
        {
            result.push_back(*iter2);
            iter2++;
        }
        //they are the same
        else if (*iter1 == *iter2)
        {
            result.push_back(*iter1);
            iter1++;
            iter2++;
        }
    }
    
    //adds the rest from the list
    if (iter1 != list1.end())
    {
        while (iter1 != list1.end())
        {
            result.push_back(*iter1);
            iter1++;
        }
    }

    if (iter2 != list2.end())
    {
        while (iter2 != list2.end())
        {
            result.push_back(*iter2);
            iter2++;
        }
    }
}

void doIntersection(const list<int>& list1, const list<int>& list2, list<int>& result)
{
    //creates iterators to safley travser list
    list<int>::const_iterator iter1 = list1.begin();
    list<int>::const_iterator iter2 = list2.begin();

    //adds fromn list 1 and 2 if they are equal
    while (iter1 != list1.end() && iter2 != list2.end())
    {   
        //skips list1 if its smaller
        if (*iter1 < *iter2)
        {
            iter1++;
        }
        //skips list2 if its smaller
        else if (*iter2 < *iter1)
        {
            iter2++;
        }
        //adds since they are equal
        else if (*iter1 == *iter2)
        {
            result.push_back(*iter1);
            iter1++;
            iter2++;
        }
    }
}

int countBinaryOnes(int num)
{
    //null check/exit statement
    if (num == 0)
        return 0;
    
    //checks for binary 1
    int one = num%2;

    //if 1 adds to the count else keep the looping
    if (one == 1)
        return  one + countBinaryOnes(num/2);
    else  
        return 0 + countBinaryOnes(num/2);
}

// Palindrome checker driver
bool isPalindrome(const string& str)
{
    //check string is at least 2 characters long
    if (str.size() <= 1)
        return true;
    
    //gets first and last characters
    char start = str[0];
    char end = str[str.size()-1];

    //compares them
    bool same = start == end;

    if (same)
    {
        std::string temp = str;
        temp.erase(0,1);
        temp.erase(temp.size()-1,1);

        return isPalindrome(temp);
    }
    else
        return false;
}
