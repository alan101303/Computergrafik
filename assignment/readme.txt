VERTEX NORMALS:
Everything went linear. No problems are to be notified.

RAY-TRIANGLE INTERSECTION:
At first glance I didn't notice that it was possible to find t (I mean this t: o+td) in the euclidean space by solving 3 linear equation. After reading the Tipp from the exercise hour about the Cramer's Rule everything went pretty straight forward. The comments in the code explain exaustively the formula that I have used.

BOUNDING BOX INTERSECTION:
Explanations about the logic of the function can be found in the file intersect_bounding_box.pdf 
In this method I use a lot of "if". In the first version I used if-else statements. This caused a lot of problems. I found out about the problem using the coverage tool of clion. I tried deleting the "esle if" and simply write "if": it worked. This is all.
