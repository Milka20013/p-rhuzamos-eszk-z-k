#include "../include/cl_utils.h"
#include <CL/cl.h>
#include <stdio.h>

cl_mem set_int_array_as_param(cl_context context, cl_kernel kernel, cl_command_queue command_queue, int *arr, int n, int arg_index)
{
    cl_mem device_a = clCreateBuffer(context, CL_MEM_READ_WRITE, n * sizeof(int), NULL, NULL);

    cl_int err = clSetKernelArg(kernel, arg_index, sizeof(cl_mem), (void *)&device_a);
    if (err != CL_SUCCESS)
    {
        printf("Setting kernel arg didn't work err: %d", err);
    }

    err = clEnqueueWriteBuffer(
        command_queue,
        device_a,
        CL_FALSE,
        0,
        n * sizeof(int),
        arr,
        0,
        NULL,
        NULL);
    if (err != CL_SUCCESS)
    {
        printf("Enqueue kernel arg didn't work err: %d", err);
    }
    return device_a;
}

cl_mem set_long_long_array_as_param(cl_context context, cl_kernel kernel, cl_command_queue command_queue, long long *arr, int n, int arg_index)
{
    cl_mem device_a = clCreateBuffer(context, CL_MEM_READ_WRITE, n * sizeof(long long), NULL, NULL);

    cl_int err = clSetKernelArg(kernel, arg_index, sizeof(cl_mem), (void *)&device_a);
    if (err != CL_SUCCESS)
    {
        printf("Setting kernel arg didn't work err: %d", err);
    }

    err = clEnqueueWriteBuffer(
        command_queue,
        device_a,
        CL_FALSE,
        0,
        n * sizeof(long long),
        arr,
        0,
        NULL,
        NULL);
    if (err != CL_SUCCESS)
    {
        printf("Enqueue kernel arg didn't work err: %d", err);
    }
    return device_a;
}