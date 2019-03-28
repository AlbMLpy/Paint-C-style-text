/**
 *
 *
 *
 *
 *
 */ 
struct Dynamic_Vec;

/**
 *
 *
 *
 *
 *
 */ 
struct Dynamic_Vec *
initialize_vec(int *error);

/**
 *
 *
 *
 *
 *
 */
int
size_vec(struct Dynamic_Vec *vec);

/**
 *
 *
 *
 *
 *
 */
void
finalize_vec(struct Dynamic_Vec *vec);

/**
 *
 *
 *
 *
 *
 */
struct Dynamic_Vec *
set_value_vec(struct Dynamic_Vec *vec, int index, int data);

/**
 *
 *
 *
 *
 *
 */
int
get_value_vec(struct Dynamic_Vec *vec, int index, int *data);

/**
 *
 *
 *
 *
 *
 */
int
print_dyn_vec(struct Dynamic_Vec *vec, int index_begin, int index_end);
