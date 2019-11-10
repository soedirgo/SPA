There is a bash script for release mode and debug mode. To run all the autotesters testing
1) cd to this directory in windows terminal
2) type "system_test_r.sh 1" where "1" or "2" or "3" is the iteration number file
"system_test_r.sh 1" , "system_test_r.sh 2"  , "system_test_r.sh 3" respectively.
3) to run the auto testers, in release mode "system_test_r.sh 1" to run in autotester debug mode 
"system_test.sh 1" without the r
however debug mode is slower than release mode, so run system_test_r.sh instead 
and permutate the number from 1 to 3.
4) To check for the results for the test autoer for each run, go to the report folder
"Team18\Code18\Tests18\Iteration1\reports" for "system_test_r.sh 1"
"Team18\Code18\Tests18\Iteration2\reports" for "system_test_r.sh 2"
"Team18\Code18\Tests18\Iteration3\reports" for "system_test_r.sh 3"

The reports are generated when the auto tester bash script completed!