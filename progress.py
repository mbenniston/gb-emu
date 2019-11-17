import subprocess

cmd="./bin/gb-asm -l | wc -l"
result = subprocess.check_output(cmd, shell=True)
numLines = int(result)
maxInst = 255 #of base instructions
progress = 100 * numLines / float(maxInst)
print(progress, "% of instructions implemented")