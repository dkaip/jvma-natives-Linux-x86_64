/*
 * freeMemory.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: Douglas Kaip
 */

#include <vector>
#include <stdlib.h>

namespace jvma
{
    void freeMemory(std::vector<void *> *memoryToFree)
    {
        if (memoryToFree->size() == 0)
            return;

        for (long unsigned int i = 0; i < memoryToFree->size(); i++)
        {
            free((*memoryToFree)[i]);
        }
    }
}



