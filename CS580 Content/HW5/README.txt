John Hessefort
UIN: 01046558

Compilation
-----------

To compile the source code file the program, run the following command from one of the ODU linux terminals:
g++ -g -c convertToCSV.cpp
g++ -g -o convert convertToCSV.o

Execution
---------
Now, with the required digit_dataset.m and optdigits-orig.windep files in the same directory as the executable file, run the standard execution command from the linux terminal.
./convert

Results
-------
After singular program execution, we find that there has been created two new .csv files, digitInput and digitTarget, that can be used in the Matlabs Neural Network pattern recognition nprtool for testing.

Neural Network Training Analysis
--------------------------------
After testing the pattern net on the converted input/output files with the same default number of training, validation, and testing samples (1257, 270, and 270 respectively) for different amounts of hidden nodes (10, 100, and 500 respectively), I found that the accuracies varied somewhat greatly.

Cross-Entropy Error
-------------------
10 Hidden Nodes: 
	- Training: Most values fall within range [1, 2.5].
	- Validation: The values average to approximately 6.55.
	- Testing: The values average to approximately 6.55.
100 Hidden Nodes:
	- Training: Range [4.5, 6.5]
	- Validation: Range [14, 18.5]
	- Testing: Range [14, 18.5]
500 Hidden Nodes:
	- Training: 7.77, 7.71, 7.99; Range [7.65, 8]
	- Validation: 23.20, 22.5, 23.408; Range [22.562, 23.408]
	- Testing: 23.09, 23.383; Range [22.965, 23.6]

Percent Misclassification Error
-------------------------------
10 Hidden Nodes:
	- Training: 3.5, 8, 1.5; Range [1.5, 7.995]
	- Validation: 5.1, 5.5, 4.444; Range [4.3, 5.5]
	- Testing: 4.4, 6.3, 5.2; Range [4.45, 6.38]
100 Hidden Nodes:
	- Training: Constant 0
	- Validation: Range [1.4, 4.5]
	- Testing: Range [1.4, 4.5]
500 Hidden Nodes:
	- Training: Constant 0
	- Validation: Range [4, 6]
	- Testing: Range [2.222, 6.423]

Analysis
--------
Let us say that the scenario in which we use only 10 hidden nodes for training is our default situation. We find that while an increase in the number of hidden nodes before training leads at some threshold to an absolute minimization of misclassification error for our training samples, there is in many cases a rather substantial increase in the cross-entropy error for our validation and testing samples. Additionally, the computational burden and execution time increases greatly with a larger amount of nodes.