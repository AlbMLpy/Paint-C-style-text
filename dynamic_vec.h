/**
 * This is a dynamic container for int values with interface below;
 */ 
struct Dynamic_Vec;

/**
 * This function initializes dynamic vector with fixed size;
 * Returns pointer on container if memory is not full, else NULL;
 */ 
struct Dynamic_Vec *
initialize_vec(void);

/**
 * This function returns the size of vec, if vec == NULL it returns -1;
 */
int
size_vec(struct Dynamic_Vec *vec);

/**
 * This function free the memory given to vec pointer;
 */
void
finalize_vec(struct Dynamic_Vec *vec);

/**
 * This function allows you to put data into vec knowing index in dynamic container;
 * Returns changed pointer vec if there are no problems with memory, else vec = NULL, 
 * and function returns NULL;
 */
struct Dynamic_Vec *
set_value_vec(struct Dynamic_Vec *vec, int index, int data);

/**
 * This function allows you to take data from vec knowing index in dynamic container;
 * Returns 0 and put int data into *data if such index is regular, else returns -1; 
 */
int
get_value_vec(struct Dynamic_Vec *vec, int index, int *data);

/**
 * This function prints contents of vec like digits to standart output;
 * If vec == NULL it does nothing; if index_begin and index_end are not appropriate 
 * function returns -1, else prints contents and returns 0;
 */
int
print_dyn_vec_digit(struct Dynamic_Vec *vec, int index_begin, int index_end);

/**
 * This function prints contents of vec like characters to standart output;
 * If vec == NULL it does nothing; if index_begin and index_end are not appropriate 
 * function returns -1, else prints contents and returns 0;
 *
 *
 */
int
print_dyn_vec_text(struct Dynamic_Vec *vec, int index_begin, int index_end);

