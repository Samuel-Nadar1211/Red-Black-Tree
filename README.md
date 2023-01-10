# Red-Black-Tree

### Properties of Red-Black Tree
<ul>
<li>A Red-Black tree is a self balancing binary search tree with one extra bit of information per node, its colour.</li>
<li>A Red-Black tree is a binary search tree that satisfies the following red-black properties:
<ol>
<li>Every node is either red or black.</li>
<li>The root of the tree is always black.</li>
<li>Every leaf nodes(NIL) are black.</li>
<li>There are no two adjacent red nodes.</li>
<li>For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.</li>
</ol></li>
<li>Time Complexity of Inserting, Deleting, Searching is O(log n), where n is the total number of nodes.</li>
<li>Height of a Red-Black tree with n nodes is h<= 2 log<sub>2</sub>(n + 1)</li>
<li>This tree was invented in 1972 by Rudolf Bayer.</li>
</ul>

### Red-Black Tree vs AVL Tree
AVL trees are strictly height balanced whereas Red-Black trees are approximated height balanced but AVL trees requires more rotations in insertion and deletion operations. Hence, Red-Black Tree is preferred over AVL tree if application involves frequent insertion and deletion operations. If search is a more frequent operation, then AVL Tree is preferred.

### Applications 
<ol><li>Most of the self-balancing BST library functions like map, multiset, and multimap in C++ ( or  java packages like java.util.TreeMap and java.util.TreeSet ) use Red-Black Trees.</li>
<li>It is used to implement CPU Scheduling Linux. Completely Fair Scheduler uses it.</li>
<li>It is also used in the K-mean clustering algorithm in machine learning for reducing time complexity.</li>
<li>Moreover, MySQL also uses the Red-Black tree for indexes on tables in order to reduce the searching and insertion time.</li></ol>

### Algorithm for Insertion
<pre>
Step 1: If tree is empty
Step 2:   Create newnode as root node with colour black
Step 3: Else (tree is not empty)
Step 4:   Create newnode as leaf with colour red performing standard BST Insertion
Step 5:   If parent of newnode is black then exit
Step 6:   Else (parent of newnode is red)
Step 7:     If colour of parent's sibbling is black or null
Step 8:       Do suitable rotation and recolour
Step 9:     Else (colour of parent's sibling is red)
Step 10:      Recolour
Step 11:      If parent's parent of newnode is not root
Step 12:        Go to step 5 and check parent's parent as newnode
Step 13:      End If
Step 14:    End If
Step 15:  End If
Step 16:End If
</pre>

### Algorithm for Deletion
<pre>
Step 1: Perform standard BST Deletion
Step 2: If node to be deleted is red
Step 3:   Just delete it
Step 4: Else
Step 5:   Make the null node double black
Step 6: End If
Step 7:  If root is double black
Step 8:     Remove double black
Step 9:  Else if double black's sibling is red
Step 10:    Swap colours of parent and sibling
Step 11:    Rotate parent in double black direction
Step 12:    Go to step 7
Step 13: Else if both the children of sibling are black (sibling is black)
Step 14:    Remove double black
Step 15:    Add black to parent (red to black or black to double black)
Step 16:    Make sibling red
Step 17:    If still double black exists, go to step 7
Step 18: Else if sibling's child who is far far from double black is black (near child is red)
Step 19:    Swap colour of double black's sibling & sibling's near child to double black
Step 20:    Rotate sibling in opposite direction to double black
Step 21:    Go to step 23
Step 22: Else (sibling's far child is red)
Step 23:    Swap colours of parent and sibling
Step 24:    Rotate parent in double black direction
Step 25:    Remove double black
Step 26:    Change colour of sibling's far child from black to red
Step 27: End If
</pre>

### UML
![UML](https://user-images.githubusercontent.com/98077236/211531198-df73776d-d5a7-438c-8b1b-f3941f506823.png)

### Screenshots
![image](https://user-images.githubusercontent.com/98077236/211507087-85e93dc5-1dd6-4f99-8270-62b1329b3155.png)

### Reference
Introduction- https://www.geeksforgeeks.org/introduction-to-red-black-tree/
Insertion- https://youtu.be/qA02XWRTBdw
Deletion- https://youtu.be/qA02XWRTBdw
