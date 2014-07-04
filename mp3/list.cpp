/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    clear(); 
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    // if we have things to delete
    if (!empty())
    {
        ListNode * curr = head;
        // iterate down the parameter list
        while (curr != NULL)
        {
            curr = head->next;
            delete head;
            head = curr;
        }
    }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    ListNode* nNode = new ListNode(ndata);
    if(empty())
    {
        head = nNode;
        tail = nNode;
        nNode->prev = NULL;
        nNode->next = NULL;
        
    }
    else
    {
        head->prev = nNode;
        nNode->next = head;
        nNode->prev = NULL;
        head = nNode;
    }
    length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    ListNode* nNode = new ListNode(ndata);
    if(empty())
    {
        head = nNode;
        tail = nNode;
        nNode->prev = NULL;
        nNode->next = NULL;       
    }
    else
    {
        tail->next = nNode;
        nNode->prev = tail;
        nNode->next = NULL;
        tail = nNode;
    }
    length++;
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    ListNode * myend = head->next->next;
    reverse(head, myend);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    if(startPoint == endPoint)
        return;
    if (!empty()) 
    {
        ListNode * original = endPoint;
        ListNode * prevNode = NULL;
        ListNode * endNext = endPoint->next;
        ListNode * myEndPoint = endPoint;
        ListNode * startPrev = startPoint->prev;

        while (original != startPrev)
        {
            ListNode * node = new ListNode(original->data);

            if (original == myEndPoint)
            {
                startPoint = node;
                node->prev = startPrev;
                if (startPrev != NULL)
                    startPrev->next = node;
                else
                    head = node;
            }

            else
            {
                node->prev = prevNode;
            }

            if (prevNode != NULL)
                prevNode->next = node;

            ListNode * temp = original;
            original = original->prev;
            if (temp != NULL && temp != myEndPoint)
            {
                delete temp;
                temp = NULL;
            }
            prevNode = node;
        }

        endPoint = prevNode;
        prevNode->next = endNext;        
        
        if (endNext != NULL)
        {
            delete endNext->prev;
            endNext->prev = prevNode;
        }
        
        else
        {
            delete tail;
            tail = prevNode;
        }

        // ListNode * test = tail;
        // while(test != NULL)
        // {
        //     cout << test->data << " ";
        //     test = test->prev;
        // }

        // cout << endl;

        // test = head;
        // while(test != NULL)
        // {
        //     cout << head->data << " ";
        //     test = test->next;
        // }
        
    }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
    if (n >= length)
        reverse(head, tail);
    if (n <= 0)
        return;
    if (empty())
        return;

    ListNode * endPt = head;
    ListNode * startPt = endPt;
    for(int i = 0; i < length; i+= n)
    {
        if (i != 0)
        {
            startPt = endPt->next;
            endPt = startPt;
        }
        for (int j = 1; j < n; j++)
        {
            if (endPt->next != NULL)
                endPt = endPt->next;
        }
        cout << "Reversing " << startPt->data << " " << endPt->data << endl;
        reverse(startPt, endPt);
    }
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    // no.
    ListNode * curr = head;
    while (curr->next != tail)
    {
        ListNode * currNext = curr->next;
        ListNode * currNextNext = currNext->next;

        curr->next = currNextNext;
        currNextNext->prev = curr;

        tail->next = currNext;
        currNext->prev = tail;
        currNext->next = NULL;

        tail = currNext;
        curr = curr->next;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    for (int i = 0; i < splitPoint; i++)
        start = start->next;
    
    start->prev->next = NULL;
    start->prev = NULL;
    
    return start;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    ListNode * startPtr = first->data < second->data? first : second;
    ListNode * temp = NULL;

    while (first != NULL && second != NULL)
    {
        
        if (first->data < second->data)
        {
            temp = first->next;
            first->next = second;
            second->prev = first;
            // cout << first->data << " ";
            first = temp;
        }
        else
        {
            temp = second->next;
            second->next = first;
            first->prev = second;
            // cout << second->data << " ";
            second = temp;
        }
    }

    
    // if (first == NULL)
    // {
    //     while (second != NULL)
    //     {
    //         cout << second->data << " ";
    //         second = second->next;
    //     }
    // }
    // if (second == NULL)
    // {
    //     while (first != NULL)
    //     {
    //         cout << first->data << " ";
    //         first = first->next;
    //     }
    // }
            
    return startPtr ;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
    return NULL; // change me!
}
