/**
 * This class allows you to store information about variable:
 * it`s type in char, and counter of anything you want;
 */
class Counter {
    int *counter_var;
    char *type_var;
    int size;
public:
    Counter(char, int);
    ~Counter();
/**
 * This function allows you to add variable into Counter with
 * identificator = id and counter = count;
 */
    void add_var(char id, int count);

/**
 * This function allows you to get count of your variable via id;
 * It returns -1 if there is no id in Counter, else count;
 */
    int get_counter(char id) const;

/**
 * This function allows you to increase count of variable 
 * knowing id of variable;
 * It returns -1 if id is not in Counter, else 0 and increases count;
 */
    int inc_counter(char id);
};
