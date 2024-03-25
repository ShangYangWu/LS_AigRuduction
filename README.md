# LogicSynthesis PA2 </BR>
M11215084 吳尚陽 </BR>

# objective </BR>
using ABC command to reduce the number of AIG gate </BR>

# HOW TO USE </BR>
step1. install ABC from https://github.com/berkeley-abc/abc.git </BR>
step2. cd abc </BR>
step3. make (to recompile, use "make clean") </BR>
step4. ./pa2.out ex00.truth (for .truth file, please put down the correct path of the file) </BR>
step5. the program will gernate ex00.script under /src </BR>
step6. mv ex00.script .. (move ex00.script to /abc) </BR>
step7. cd .. (go to /abc) </BR>
step8. ./abc -c "ex00.script" </BR>
step9. ABC will gernerate ex00.aig under /abc </BR>
step10. ./abc </BR>
step11. read ex00.aig </BR>
step12. cec -n ex00.truth (for .truth file, please put down the correct path of the file) </BR>
step13. print_stats </BR>
step14. quit </BR>
