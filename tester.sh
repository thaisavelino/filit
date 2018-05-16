for elem in tests/*; do echo "${elem}\n"; cat -e "${elem}"; printf "\n"; time ./fillit "${elem}"; printf "\n"; read -p "Press any key to proceed"; clear; done
