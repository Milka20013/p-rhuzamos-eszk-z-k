#include "utils/include/file_utils.h"
#include "utils/include/matrix_utils.h"
#include "utils/include/bigint_utils.h"
#include "utils/include/cl_utils.h"

#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>
#include <time.h>

const int SAMPLE_SIZE = 5000;

int main(void)
{
    clock_t begin = clock();
    char *filename = "clSource.cl";
    int count = 0;
    int error = count_chars_in_file(filename, &count);

    String *str = malloc(sizeof(String));
    build_empty_string(str, count + 16);
    store_file_in_string(str, filename);
    str->content[str->length - 1] = '\0';
    int i;
    cl_int err;

    // Get platform
    cl_uint n_platforms;
    cl_platform_id platform_id;

    err = clGetPlatformIDs(1, &platform_id, &n_platforms);
    if (err != CL_SUCCESS)
    {
        printf("[ERROR] Error calling clGetPlatformIDs. Error code: %d\n", err);
        return 0;
    }

    // Get device
    cl_device_id device_id;
    cl_uint n_devices;
    err = clGetDeviceIDs(
        platform_id,
        CL_DEVICE_TYPE_GPU,
        1,
        &device_id,
        &n_devices);
    if (err != CL_SUCCESS)
    {
        printf("[ERROR] Error calling clGetDeviceIDs. Error code: %d\n", err);
        return 0;
    }

    // Create OpenCL context
    cl_context context = clCreateContext(NULL, n_devices, &device_id, NULL, NULL, NULL);

    // Build the program
    cl_program program = clCreateProgramWithSource(context, 1, &(str->content), NULL, NULL);
    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Build error! Code: %d\n", err);
        size_t real_size;
        err = clGetProgramBuildInfo(
            program,
            device_id,
            CL_PROGRAM_BUILD_LOG,
            0,
            NULL,
            &real_size);
        char *build_log = (char *)malloc(sizeof(char) * (real_size + 1));
        err = clGetProgramBuildInfo(
            program,
            device_id,
            CL_PROGRAM_BUILD_LOG,
            real_size + 1,
            build_log,
            &real_size);
        // build_log[real_size] = 0;
        printf("Real size : %d\n", real_size);
        printf("Build log : %s\n", build_log);
        free(build_log);
        return 0;
    }
    if (err != CL_SUCCESS)
    {
        printf("Build error! Code: %d\n", err);
        return 0;
    }
    cl_kernel kernel = clCreateKernel(program, "hello_kernel", NULL);
    //----
    //----
    //----
    // Create the host buffer and initialize it
    const int length_int = 1;
    const int length_long_long = 9;
    const int length_str = 800;
    unsigned char *number_str = generate_random_digits(length_str, 0);
    /*for (int i = 0; i < length_str; i++)
    {
        printf("%c", number_str[i]);
    }*/

    int a;
    int *aArr = create_int_array_n_from_str(number_str, length_int, &a);
    int b;
    int *bArr = create_int_array_n_from_str(number_str, length_int, &b);
    free(number_str);

    int *result = malloc(sizeof(int) * (a + b));

    int *subResults = (int *)malloc(a * (a + b) * sizeof(int));
    if (subResults == NULL)
    {
        fprintf(stderr, "Memory allocation failed dum dum\n");
        exit(1);
    }

    int *carries_device = (int *)malloc((a + b) * sizeof(int));
    if (carries_device == NULL)
    {
        fprintf(stderr, "Memory allocation failed dum dum2\n");
        exit(1);
    }
    // program begins here
    begin = clock();

    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, NULL);
    set_int_array_as_param(context, kernel, command_queue, aArr, a, 0);
    set_int_array_as_param(context, kernel, command_queue, bArr, b, 1);
    cl_mem device_result = set_int_array_as_param(context, kernel, command_queue, result, a + b, 2);

    cl_mem subresults = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * a * (a + b), NULL, &err);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&subresults);

    cl_mem carries = set_int_array_as_param(context, kernel, command_queue, carries_device, a + b, 4);

    cl_mem a_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int), NULL, &err);
    clSetKernelArg(kernel, 5, sizeof(a_mem), (void *)&a);

    cl_mem b_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int), NULL, &err);
    clSetKernelArg(kernel, 6, sizeof(b_mem), (void *)&b);

    // set_int_array_as_param(context, kernel, command_queue, n_as_arr, 1, 3);

    // Size specification
    size_t local_work_size[] = {b};
    size_t global_work_size[] = {b};

    // Apply the kernel on the range
    cl_event event;
    error = clEnqueueNDRangeKernel(
        command_queue,
        kernel,
        1,
        NULL,
        global_work_size,
        NULL,
        0,
        NULL,
        &event);
    if (error != CL_SUCCESS)
    {
        printf("%d as", error);
        return 0;
    }
    clWaitForEvents(1, &event);

    // Host buffer <- Device buffer
    error = clEnqueueReadBuffer(
        command_queue,
        carries,
        CL_TRUE,
        0,
        sizeof(int) * (a + b),
        carries_device,
        0,
        NULL,
        NULL);
    error = clEnqueueReadBuffer(
        command_queue,
        device_result,
        CL_TRUE,
        0,
        sizeof(int) * (a + b),
        result,
        0,
        NULL,
        NULL);
    error = clEnqueueReadBuffer(
        command_queue,
        subresults,
        CL_TRUE,
        0,
        sizeof(int) * a * (a + b),
        subResults,
        0,
        NULL,
        NULL);
    if (error != CL_SUCCESS)
    {
        printf("%d asd", error);
        return 0;
    }
    /*printf("\n carries: ");
    for (int i = 0; i < a + b; i++)
    {
        printf(" %d ", carries_device[i]);
    }*/

    int tmp = 0;
    int carry = 0;
    int tenRemainder = 0;
    for (int i = a + b - 2; i >= 1; i--)
    {
        tmp = result[i] + carries_device[i + 1];
        tenRemainder = tmp % 10;
        result[i] = tenRemainder;
        carry = (tmp - tenRemainder) / 10;
        carries_device[i] += carry;
    }

    /*printf("\n results: ");
    for (int i = 0; i < a + b; i++)
    {
        printf(" %d ", result[i]);
    }*/

    //----
    //----
    //----
    clFinish(command_queue);

    cl_ulong time_start;
    cl_ulong time_end;

    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

    double nanoSeconds = time_end - time_start;
    printf("OpenCl Execution time is: %0.3f milliseconds \n", nanoSeconds / 1000000.0);
    // Release the resources
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseContext(context);
    clReleaseDevice(device_id);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Program Execution time is: %0.3lf seconds or %0.3lf milliseconds\n", time_spent, time_spent * 1000);

    begin = clock();
    multiply_int_big_nums(aArr, bArr, a, b, result);
    end = clock();

    free(aArr);
    free(bArr);
    free(result);
    free(subResults);

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sequential Execution time is: %0.3lf seconds or %0.3lf milliseconds\n", time_spent, time_spent * 1000);
}
