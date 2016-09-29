import os

EX = 'IntMatrixMainDriver'
CASES = "tests/cases_lite"
failed = 0

if not os.path.exists("tests/results"):
    os.makedirs("tests/results")

if not os.path.exists("tests/diffs"):
    os.makedirs("tests/diffs")

if not os.path.exists("tests/vlg"):
    os.makedirs("tests/vlg")

os.system("rm -rf tests/results/* tests/diffs/* tests/vlg/* tests/summary.out")

r = open("tests/summary.out", "w+")

for test in os.listdir(CASES):
	os.system(EX + " < " + CASES + "/" + test + " > tests/results/" + test[:-3] + ".out")
	os.system("diff tests/school/" + test[:-3] + ".out tests/results/" + test[:-3] + ".out > tests/diffs/"  + test + ".diff")
	if os.path.getsize("tests/diffs/"  + test + ".diff") > 0:
		r.write("FAILED "+test+"\n")
		failed = failed + 1
print "TOTAL FAILED: ", failed

for test in os.listdir(CASES):
	os.system("valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes " + EX + " < " + CASES + "/" + test + " > tests/vlg/" + test[:-3] + ".vlg")
r.close()

