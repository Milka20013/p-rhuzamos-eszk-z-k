#include "utils/include/file_utils.h"
#include "utils/include/matrix_utils.h"

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

    // Create the host buffer and initialize it
    unsigned N = 64;
    MatrixF matrix1 = create_matrix(N, N);
    MatrixF matrix2 = create_matrix(N, N);
    MatrixF resultMatrix = create_matrix(N, N);
    float *element;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            element = get_matrix_element(&matrix1, i, j);
            (*element) = (i + 1) * (j + 1) * 0 + 1;
            element = get_matrix_element(&matrix2, i, j);
            (*element) = (i + 1) * (j + 1) * 0 + 1;
        }
    }
    // Create the device buffer
    cl_mem device_a = clCreateBuffer(context, CL_MEM_READ_WRITE, N * N * sizeof(float), NULL, NULL);
    cl_mem device_b = clCreateBuffer(context, CL_MEM_READ_WRITE, N * N * sizeof(float), NULL, NULL);
    cl_mem device_c = clCreateBuffer(context, CL_MEM_READ_WRITE, N * N * sizeof(float), NULL, NULL);
    cl_mem device_n = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int), NULL, NULL);

    // Set kernel arguments
    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&device_a);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&device_b);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&device_c);
    clSetKernelArg(kernel, 3, sizeof(int), (void *)&N);

    // Create the command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, NULL);
    // Host buffer -> Device buffer
    error = clEnqueueWriteBuffer(
        command_queue,
        device_a,
        CL_FALSE,
        0,
        N * N * sizeof(float),
        matrix1.data,
        0,
        NULL,
        NULL);
    error = clEnqueueWriteBuffer(
        command_queue,
        device_b,
        CL_FALSE,
        0,
        N * N * sizeof(float),
        matrix2.data,
        0,
        NULL,
        NULL);
    error = clEnqueueWriteBuffer(
        command_queue,
        device_c,
        CL_FALSE,
        0,
        N * N * sizeof(float),
        matrix2.data,
        0,
        NULL,
        NULL);
    if (error != CL_SUCCESS)
    {
        printf("%d a", error);
        return 0;
    }

    // Size specification
    size_t local_work_size[] = {N, N};
    // size_t n_work_groups = (N * N + local_work_size + 1) / local_work_size;
    size_t global_work_size[] = {N * 16, N * 16};

    // Apply the kernel on the range
    cl_event event;
    error = clEnqueueNDRangeKernel(
        command_queue,
        kernel,
        2,
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
        device_c,
        CL_TRUE,
        0,
        N * N * sizeof(float),
        resultMatrix.data,
        0,
        NULL,
        NULL);
    if (error != CL_SUCCESS)
    {
        printf("%d asd", error);
        return 0;
    }
    clFinish(command_queue);

    cl_ulong time_start;
    cl_ulong time_end;

    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

    double nanoSeconds = time_end - time_start;
    print_matrix(&resultMatrix);
    printf("OpenCl Execution time is: %0.3f milliseconds \n", nanoSeconds / 1000000.0);

    // print_matrix(&resultMatrix);

    // Release the resources
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseContext(context);
    clReleaseDevice(device_id);

    delete_matrix(&matrix1);
    delete_matrix(&matrix2);
    delete_matrix(&resultMatrix);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nProgram Execution time is: %0.3lf seconds or %0.3lf milliseconds", time_spent, time_spent * 1000);
}
