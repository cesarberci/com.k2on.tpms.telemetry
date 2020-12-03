/*
 * utils.c
 *
 *  Created on: 27/02/2020
 *      Author: cesar
 */

#include "utils.h"

void __run(void (*function)(void))
{
  if (function > 0)
    function();
}

