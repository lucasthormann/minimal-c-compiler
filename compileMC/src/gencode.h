#ifndef GENCODE_H
#define GENCODE_H
#define nextlabel() (++labelcounter)
#define resetregisters() (registercounter=7)

#include "tree.h"

void setup_frame();
void reset_registers();
void set_return_value();
void syscall_for_clean_exit();
void teardown_frame_and_restore();
void make_header();
void make_footer();
int get_register();
int gencode(tree *ast);

                       
                       
                       

#endif
