/**
 * This class allows you to store information about variable:
 * it`s type in char, and counter of anything you want;
 */
template <typename Index>
class Counter {
    int counter_var;
    Index id;
public:
    Counter(Index id);
    ~Counter(){};
/**
 * This function allows you to get count of your variable;
 * It returns -1 if there is no id in Counter, else count;
 */
    int get_counter() const;

/**
 * This function allows you to increase count of variable;
 */
    void inc_counter();

/**
 * This function returns type of variable to connect with;
 */
   Index get_id() const;

};


template <typename Index>
Counter<Index>::Counter(Index id_num)
{
    counter_var = 0;
    id = id_num;
}    

template <typename Index>
int
Counter<Index>::get_counter() const
{
    return counter_var; 
}

template <typename Index>
void
Counter<Index>::inc_counter()
{
    counter_var++;
    return;   
}    

template <typename Index>
Index Counter<Index>::get_id() const 
{
    return id;
}
