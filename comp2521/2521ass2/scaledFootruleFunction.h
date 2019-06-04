#include "list.h"


void SFR(int argc, char *argv[]);

List Read_file(char *file_name);

List label_list(List *L);

List add_to_label(List L, List n);

void recursion_bruteforce(int step, int best[], List C, List T[]);

void foot_rule_min(int best[], List C, List T[]);

