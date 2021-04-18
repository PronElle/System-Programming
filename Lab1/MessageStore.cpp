//
// Created by elle on 24/03/21.
//

#include <cstring>
#include "MessageStore.h"
#define DEBUG()

MessageStore::MessageStore(int _n): n(_n), dim(_n), next_pos(0){
    messages = new (std::nothrow) Message[n];
}


MessageStore::~MessageStore() {
   if(messages != nullptr){
       delete[] messages;
       messages = nullptr;
   }
}

/**
 * adds a given message iff
 *  - its valid
 *  - has a unique id
 * resizes the array if needed
 * @param m: message to add
 */
void MessageStore::add(Message &m) {
    if(m.getId() == -1)
        return;

    // if msg with given id already exists
    if(find(m.getId()) >= 0)
        return;

    // if no available space to store the new msg
    if(next_pos >= dim) {
        // reallocating memory
       resize(dim + n);
    }

    // storing new msg
    messages[next_pos++] = m;

#ifdef DEBUG
    std::cout << "added msg with id: " << m.getId() << std::endl;
#endif
}


/**
 * retrives message with given id, if
 * it exists
 * @param id
 * @return msg
 */
std::optional<Message> MessageStore::get(long id) {
    int pos = find(id);

    if(pos >= 0)
        return messages[pos];
    else
        return std::nullopt;
}

/**
 * removes a message of given id, if present
 * (removing means replacing with an empty one)
 * @param id
 * @return true if message found and removed, false otherwise
 */
bool MessageStore::remove(long id) {
    int pos = find(id);

    if(pos >= 0){
        #ifdef DEBUG
        std::cout << "removed msg with id: " << id << std::endl;
        #endif
        // replacing with empty msg (specifications)
        messages[pos] = Message();
        return true;
    }

    return false;
}

/**
 * retrieves the number of valid messages
 * and the number of free slots
 * @return tuple
 */
std::tuple<int, int> MessageStore::stats() {
    int valid = 0;

    for(int i = 0; i < next_pos ; ++i)
        if(messages[i].getId() != -1)
            valid ++;

    return std::tuple<int, int>(valid, dim - next_pos);
}

/**
 * deletes empty cells and reduces dim to
 * the minimum multiple of n
 */
void MessageStore::compact() {
    int non_empty = 0;
    for(int i=0; i<dim; i++){
        non_empty += messages[i].getId() >=0 ? 1 : 0;
    }

    int new_dim = non_empty % n == 0 ? non_empty : (1 + non_empty/n) * n;
    resize(new_dim);
}

/**
 * detects if a message of given id exists in
 * the message array and retrieves its index
 * @param id
 * @return index if message exists, -1 otherwise
 */
int MessageStore::find(long id) {
    for(int i = 0; i < next_pos ; ++i)
        if(messages[i].getId() == id)
            return i;

    return -1;
}

/**
 * resizes array of messages allocating a new one
 * of size "size"
 * @param size : requested new size
 * */
void MessageStore::resize(int size) {
    // temporary buffer
    Message *new_msgs = new Message[size]; // auto avoided on purpose

    // Copying all VALID messages
    int valid = 0;
    for (int i = 0; i < dim; i++)
        if(messages[i].getId() != -1 )
            new_msgs[valid++] = messages[i];

    // deleting data from previous array
    delete[] messages;

    // allocating a new array of Message with proper dimension
    messages = new_msgs;

    // Updating dim according to new size
    // and next free position according to current occupation
    dim = size;
    next_pos = valid;
}



