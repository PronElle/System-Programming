//
// Created by elle on 24/03/21.
//

#include <cstring>
#include "MessageStore.h"

MessageStore::MessageStore(int _n): n(_n), dim(_n), next_pos(0){
    messages = new (std::nothrow) Message[n];

    if(messages != nullptr){
        // TODO: to be implemeneted
    }

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

    if(find(m.getId()))
        return;

    if(next_pos >= dim) {
        // reallocating memory
        Message* tmp = nullptr;
        tmp = messages;

        messages = new (std::nothrow) Message [dim + n];
        for(int i = 0; i < dim; ++i)
            messages[i] = tmp[i];

        dim += n;
        delete[] tmp;
    }

    messages[next_pos ++] = m;
}


/**
 *
 * @param id
 * @return
 */
std::optional<Message> MessageStore::get(long id) {
    // TODO: to be implemented
    return std::optional<Message>();
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
    // TODO: to be implemented
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



