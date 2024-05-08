/*
 * kernel_module_example.h
 *
 *  Created on: Apr 27, 2024
 *      Author: Xiang-Guan Deng
 */

#ifndef DEBUG_ACCESS_H_
#define DEBUG_ACCESS_H_


struct kernel_module_example_dev
{
  bool is_open_;
  int val;
  struct cdev cdev;
};


#endif /* DEBUG_ACCESS_H_ */