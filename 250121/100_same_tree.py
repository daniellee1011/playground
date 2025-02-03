# 100. Same Tree

from typing import Optional
from collections import deque

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        p_deque = deque([p])
        q_deque = deque([q])

        while p_deque and q_deque:
            p_pop = p_deque.popleft()
            q_pop = q_deque.popleft()

            if p_pop.val != q_pop.val:
                return False
            
            if p_pop.left:
                p_deque.append(p_pop.left)
            if p_pop.right:
                p_deque.append(p_pop.right)

            if q_pop.left:
                q_deque.append(q_pop.left)
            if q_pop.right:
                q_deque.append(q_pop.right)

        return False if p_deque or q_deque else True
