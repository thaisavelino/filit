for elem in tests/*; do echo "${elem}\n"; ./fillit "${elem}"; printf "\n"; done > output_tests.txt; more output_tests.txt;
