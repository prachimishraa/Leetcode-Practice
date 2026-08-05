/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *prev = &dummy, *curr = head;

        while (true) {
            ListNode *node = curr;
            int cnt = 0;
            while (node && cnt < k) {
                node = node->next;
                cnt++;
            }
            if (cnt < k) break;

            ListNode *next = node;
            ListNode *p = curr, *q = next;

            for (int i = 0; i < k; i++) {
                ListNode *temp = p->next;
                p->next = q;
                q = p;
                p = temp;
            }
            prev->next = q;
            prev = curr;
            curr = next;
        }
        return dummy.next;
    }
};