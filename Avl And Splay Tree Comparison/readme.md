# Comparison of Avl Trees and Splay Trees
In this project, program compares the performance of AVL and Splay trees based on theses two criteria: the total number of comparisons and the number of rotations.
Program accepts input as text file. Only the non-existing keys will be added. In splay tree if the key already exists the key is splayed. For the AVL tree 
if there is an AVL condition violation after inserting the new node, program makes the proper rotation and satisfies the AVL conditions.
For the splay tree, program will make the necessary splays after reading each key in the given input. 
## Comparison
The number of comparisons will be considered for both the successful and the unsuccessful searches.
The number of rotations in AVL trees will be considered only when there is a need for rotation.
A single rotation in AVL trees costs one time unit (tu) (which is equal to the cost of the comparison of two
keys), while a double rotation costs two tu's. A splay in splay trees costs as many tu's as the number of depth
levels the nodes have moved through. In Splay trees, on the other hand, there will be rotations after reading
each character from the text . 
