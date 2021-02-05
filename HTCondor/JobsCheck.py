import sys
import os

for i in range(int(sys.argv[2])):
    err_file = "run_" + sys.argv[1] + "_" + str(i) + ".err"
    if os.path.isfile(err_file):
        count_error = -1
        with open(err_file) as f:
            for line in f:
                count_error += line.count("Error in")
        if count_error != 0:
            print('Errors in job ' + str(i) + ': ' + str(count_error))
    else:
        print('Errors in job ' + str(i) + ': no file')
