#ifndef CL_WRAPPER_H
#define CL_WRAPPER_H

#ifdef __APPLE__
  #include <OpenCL/opencl.h>
#elif __linux__
  #include <CL/cl.h>
#else
  #error Not sure where to find OpenCL header
#endif

#include <map>
#include <string>
#include <vector>

using namespace std;

cl_uint query_num_platforms();
cl_platform_id *&get_platform_list();
cl_uint query_num_devices(cl_platform_id platform);
cl_device_id *get_device_list(cl_platform_id platform);
void context_error_callback(const char *errinfo, const void *private_info, size_t cb, void *user_data);
string clinfo();

class CLWrapper {
  private:
    cl_uint num_platforms;
    cl_platform_id *platforms;
    int p;

    cl_uint num_devices;
    cl_device_id *devices;
    int d;

    bool profiling;
    cl_context context;
    cl_command_queue command_queue;
    vector<cl_program> programs;
    map<string,cl_kernel> kernelmap;
    vector<cl_mem> memobjs;

    float timestamp_diff_in_ms(cl_ulong start, cl_ulong end);
    float time_and_release_event(cl_event e);
    
    void attach_context(bool all_devices=false);
    void attach_command_queue(cl_command_queue_properties properties=0);

  public:
    CLWrapper(int p=0, int d=0, bool profiling=false);
    ~CLWrapper();
    cl_program &compile(const char *fname,
        const string &extra_flags="",
        map<string,string> substitutions=(map<string,string>()),
        bool all_devices=false);

    cl_mem &dev_malloc(size_t size, cl_mem_flags flags=CL_MEM_READ_WRITE);
    void dev_free(cl_mem m);
    void free_all_memobjs();

    float memcpy_to_dev(cl_mem buffer, size_t size, const void *ptr, size_t offset=0);
    float memcpy_from_dev(cl_mem buffer, size_t size, void *ptr, size_t offset=0);
    float copy_buffer(cl_mem src, cl_mem dst, size_t cb);

    void create_all_kernels(cl_program program);
    cl_kernel &create_kernel(cl_program program, const char*kernel_name);
    cl_kernel &kernel_of_name(const string name);
    void run_kernel(cl_kernel kernel, 
      cl_uint work_dim,
      const size_t *global_work_size,
      const size_t *local_work_size,
      const size_t *global_work_offset=NULL,
      cl_uint num_events_in_wait_list=0,
      const cl_event *event_wait_list=NULL,
      cl_event *event=NULL);
    float run_kernel_with_timing(cl_kernel kernel,
      cl_uint work_dim,
      const size_t *global_work_size,
      const size_t *local_work_size,
      const size_t *global_work_offset=NULL,
      cl_uint num_events_in_wait_list=0,
      const cl_event *event_wait_list=NULL);
};

#endif
