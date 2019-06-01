# Missionaries-Cannibals-Problem
Basic AI puzzle using a variety of search algorithms including, depth-first, breadth-first, bi-directional, iterative-deepening, etc.

The problem is as follows:
"On one bank of a river are three missionaries and three cannibals. There is one boat available that can hold up to two people and that they would like to use to cross the river. If the cannibals ever outnumber the missionaries on either of the river’s banks, the missionaries will get eaten."

Each bank of the river is represented as an array of integers, index 0 being a missionary, index 1 a cannibal, and index representing the boat (1 having the boat nad 0 not)

Output:
<pre>
Start: 3 3: 1
End:   0 0: 0

Start: 2 2: 0
End:   1 1: 1

Start: 3 2: 1
End:   0 1: 0

Start: 3 0: 0
End:   0 3: 1

Start: 3 1: 1
End:   0 2: 0

Start: 1 1: 0
End:   2 2: 1

Start: 2 2: 1
End:   1 1: 0

Start: 0 2: 0
End:   3 1: 1

Start: 1 2: 1
End:   2 1: 0

Start: 0 1: 0
End:   3 2: 1

Start: 1 1: 1
End:   2 2: 0

Start: 0 0: 0
End:   3 3: 1
</pre>
