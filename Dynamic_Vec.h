/**
 * This is a dynamic container for int values with interface below;
 */
class Dynamic_Vec 
{
    int *container;
    int size;
public:
    Dynamic_Vec();    
    ~Dynamic_Vec();
    Dynamic_Vec(const Dynamic_Vec &vec);
/**
 * This function returns the size of vec, if vec == NULL it returns -1;
 */   
    int get_size() const;

/**
 * This function allows you to put data into vec knowing index in dynamic container;
 * Returns 0 if there are no problems with memory, else vec is destructed, 
 * and function returns -1;
 */
    int set_value(int index, int data);

/**
 * This function allows you to take data from vec knowing index in dynamic container;
 * Returns 0 and put int data into data if such index is regular, else returns -1; 
 */
    int get_value(int index, int &data) const;

/**
 * This function prints contents of vec like digits to standart output;
 * If vec == NULL it does nothing; if index_begin and index_end are not appropriate 
 * function returns -1, else prints contents and returns 0;
 */
    int print_digit(int begin, int end) const;

/**
 * This function prints contents of vec like characters to standart output;
 * If vec == NULL it does nothing; if index_begin and index_end are not appropriate 
 * function returns -1, else prints contents and returns 0;
 */   
    int print_text(int begin, int end) const;
};

