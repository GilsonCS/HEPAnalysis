import sys

log_file = "run_" + sys.argv[1] + ".log"

count_submitted = 0
count_terminated = 0
count_aborted = 0
with open(log_file) as f:
    for line in f:
        count_submitted += line.count("submitted")
        count_terminated += line.count("terminated.")
        count_aborted += line.count("aborted")
        
print('Jobs submitted:  ' + str(count_submitted))
print('Jobs terminated: ' + str(count_terminated))
print('Jobs aborted:    ' + str(count_aborted))
