//
// Created by elle on 24/03/21.
//

#include <cstring>
#include "MessageStore.h"

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
    if(find(m.getId()))
        return;

    // if no available space to store the new msg
    if(next_pos >= dim) {
        // reallocating memory
       resize();
    }

    // storing new msg
    messages[next_pos++] = m;
}


/**
 * retrives message with given id, if
 * it exists
 * @param id
 * @return msg
 */
std::optional<Message> MessageStore::get(long id) {
    if (id != -1) {
        for (int i = 0; i < dim; i++)
            if (messages[i].getId() == id)
                return messages[i];
    }

    return std::nullopt;
}

/**
 * removes a message of given id, if present
 * (removing means replacing with an empty one)
 * @param id
 * @return true if message found and removed, false otherwise
 */
bool MessageStore::remove(long id) {
    for(int i = 0; i < next_pos - 1; ++i)
        if(messages[i].getId() == id){
            // replacing with empty msg (specifications)
            messages[i] = Message();
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

    for(int i = 0; i < next_pos - 1; ++i)
        if(messages[i].getId() != -1)
            valid ++;

    return std::tuple<int, int>(valid, dim - next_pos);
}

/**
 * deletes empty cells and reduces dim to
 * the minimum multiple of n
 */
void MessageStore::compact() {

}

/**
 * detects if a message of given id exists in
 * the message array
 * @param id
 * @return true if message exists, false otherwise
 */
bool MessageStore::find(long id) {
    for(int i = 0; i < next_pos - 1; ++i)
        if(messages[i].getId() == id)
            return true;

    return false;
}

/**
 * resizes array of messages if a bigger
 * one is needed, allocating "n" more cells
 */
void MessageStore::resize() {
    // temporary buffer
    Message *tmp = new Message[dim]; // auto avoided on purpose

    // Copying all the messages
    for (int i = 0; i < dim; i++)
        tmp[i] = messages[i];

    // deleting data from previous array
    delete[] messages;
    messages = nullptr;

    // allocating a new array of Message with proper dimension
    messages = new Message[dim + n];

    // Copy all the values from temp buffer
    for (int i = 0; i < dim; i++)
        messages[i] = tmp[i];

    // Deleting the temporary buffer
    delete[] tmp;
    tmp = nullptr;

    // Updating the dim value
    dim += n;
}



