struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
            val(x), next(NULL) {
    }
};

//class Solution {
//public:
//	//µÝ¹é
//    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
//    {
//        if(pHead1==pHead2)
//            return pHead1;
//        if(pHead1==NULL)
//            return pHead2;
//        if(pHead2==NULL)
//            return pHead1;
//        
//        if(pHead1->val < pHead2->val)
//            {
//            pHead1->next=Merge(pHead1->next,pHead2);
//            return pHead1;
//        }
//        else      // pHead1->val >= pHead2->val
//            {
//            pHead2->next=Merge(pHead1,pHead2->next);    
//            return pHead2;
//        }
//	};


class Solution {
public:
	//·ÇµÝ¹é
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(pHead1==pHead2)
            return pHead1;
        if(pHead1==NULL)
            return pHead2;
        if(pHead2==NULL)
            return pHead1;
        ListNode* NewHead=NULL;
        ListNode* tail=NULL;
        ListNode* cur1=pHead1;
        ListNode* cur2=pHead2;
        while(cur1 && cur2)
            {
            
        }
        if(cur1->val < cur2->val)
            {
            NewHead=cur1;
            tail=cur1;
            cur1=cur1->next;
        }
        else
        {
            NewHead=cur2;
            tail=cur2;
            cur2=cur2->next;
        }
        while(cur1 && cur2)
            {
            if(cur1->val < cur2->val)
                {
                tail->next=cur1;
                tail=tail->next;
                cur1=cur1->next;
            }
            else
                {
                tail->next=cur2;
                tail=tail->next;
                cur2=cur2->next;
            }
        }
        
        if(cur1==NULL)
            {
            tail->next=cur2;
            tail=tail->next;
        }
        else
            {
            tail->next=cur1;
            tail=tail->next;
        }
        return NewHead;
    }
};