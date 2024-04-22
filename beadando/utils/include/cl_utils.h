#ifndef CL_UTILS_H
#define CL_UTILS_H

#include <CL/cl.h>

cl_mem set_int_array_as_param(cl_context context, cl_kernel kernel, cl_command_queue command_queue, int *arr, int n, int arg_index);
cl_mem set_long_long_array_as_param(cl_context context, cl_kernel kernel, cl_command_queue command_queue, long long *arr, int n, int arg_index);

#endif