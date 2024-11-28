1D PERLIN NOISE - ALAN BRAGALINI:
The structure of the code follows the structure of the assignment. There are 4 Steps and the "title" of the Step explains what is being done. 
The first small difficulty was to understand that I had to use the first component of the gradients. The second bigger difficulty was to understand how to fix Step 2. The problem was probably caused by delays or rounding problems. I am still not sure.
If the program is run with the following code for Step 2:
	vec2 grad[2];
	int a, b;
	a = hash_func(vec2(leftCellCorner, 0));
	b = hash_func(vec2(rightCellCorner, 0));
	grad[0] = gradients[(a%NUM_GRADIENTS)];
	grad[1] = gradients[(b%NUM_GRADIENTS)];

The last "wave" is going to be ugly. I cannot explain how, but the problem disappear if %NUM_GRADIENTS is added after calculating the hash_func(). Another interesting thing is, that if you run this code:
	vec2 grad[2];
	int a, b;
	a = hash_func(vec2(leftCellCorner, 0))%NUM_GRADIENTS;
	b = hash_func(vec2(rightCellCorner, 0))%NUM_GRADIENTS;
	grad[0] = gradients[(a)];
	grad[1] = gradients[(b)];
The last "wave" disappears. (at least on my laptop, today)


2D PERLIN NOISE - ALAN BRAGALINI:
I have structured the code for this method in Steps, too. The titles explain what each Step does.
There was no particular problem. The debugging of this method consisted simply in correcting the types of the variables I used. Everything worked out fine after doing that.

FBM AND TURBOLENCE - RICHIE SASEETHARAN:


TEXTURES - RICHIE SASEETHARAN:


TERRAIN - FRANCESCO LAM:
For the resolution of the task, not much trouble.
I had some compiling issues because I was trying to run the executionable without the proper build. Besides that, it looks fine.
