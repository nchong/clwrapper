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

    void set_kernel_arg(cl_kernel k, int i, int &n);
    void set_kernel_arg(cl_kernel k, int i, float &n);
    void set_kernel_arg(cl_kernel k, int i, double &n);
    void set_kernel_arg(cl_kernel k, int i, cl_mem &m);
    void set_kernel_arg(cl_kernel k, int i, size_t &l);

    // don't support copying
    CLWrapper(const CLWrapper& that);
    CLWrapper& operator=(const CLWrapper& that);

  public:
    CLWrapper(int p=0, int d=0, bool profiling=false, bool all_devices=false);
    ~CLWrapper();
    cl_program &compile(const char *fname,
        const string &extra_flags="",
        bool all_devices=false);
    cl_program &compile_from_string(const char *program_string,
        const string &extra_flags="",
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
    const string name_of_kernel(cl_kernel kernel);
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

    //
    // auto-generated by gen_kernelargs_template.py
    //
    template< typename T0 >
    inline void kernel_arg(cl_kernel k, T0 &a0 ) {
      set_kernel_arg(k, 0, a0);
    }

    template< typename T0, typename T1 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
    }

    template< typename T0, typename T1, typename T2 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
    }

    template< typename T0, typename T1, typename T2, typename T3 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
      set_kernel_arg(k, 8, a8);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8, T9 &a9 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
      set_kernel_arg(k, 8, a8);
      set_kernel_arg(k, 9, a9);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8, T9 &a9, T10 &a10 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
      set_kernel_arg(k, 8, a8);
      set_kernel_arg(k, 9, a9);
      set_kernel_arg(k, 10, a10);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8, T9 &a9, T10 &a10, T11 &a11 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
      set_kernel_arg(k, 8, a8);
      set_kernel_arg(k, 9, a9);
      set_kernel_arg(k, 10, a10);
      set_kernel_arg(k, 11, a11);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8, T9 &a9, T10 &a10, T11 &a11, T12 &a12 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
      set_kernel_arg(k, 8, a8);
      set_kernel_arg(k, 9, a9);
      set_kernel_arg(k, 10, a10);
      set_kernel_arg(k, 11, a11);
      set_kernel_arg(k, 12, a12);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8, T9 &a9, T10 &a10, T11 &a11, T12 &a12, T13 &a13 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
      set_kernel_arg(k, 8, a8);
      set_kernel_arg(k, 9, a9);
      set_kernel_arg(k, 10, a10);
      set_kernel_arg(k, 11, a11);
      set_kernel_arg(k, 12, a12);
      set_kernel_arg(k, 13, a13);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8, T9 &a9, T10 &a10, T11 &a11, T12 &a12, T13 &a13, T14 &a14 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
      set_kernel_arg(k, 8, a8);
      set_kernel_arg(k, 9, a9);
      set_kernel_arg(k, 10, a10);
      set_kernel_arg(k, 11, a11);
      set_kernel_arg(k, 12, a12);
      set_kernel_arg(k, 13, a13);
      set_kernel_arg(k, 14, a14);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8, T9 &a9, T10 &a10, T11 &a11, T12 &a12, T13 &a13, T14 &a14, T15 &a15 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
      set_kernel_arg(k, 8, a8);
      set_kernel_arg(k, 9, a9);
      set_kernel_arg(k, 10, a10);
      set_kernel_arg(k, 11, a11);
      set_kernel_arg(k, 12, a12);
      set_kernel_arg(k, 13, a13);
      set_kernel_arg(k, 14, a14);
      set_kernel_arg(k, 15, a15);
    }

    template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16 >
    inline void kernel_arg(cl_kernel k, T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8, T9 &a9, T10 &a10, T11 &a11, T12 &a12, T13 &a13, T14 &a14, T15 &a15, T16 &a16 ) {
      set_kernel_arg(k, 0, a0);
      set_kernel_arg(k, 1, a1);
      set_kernel_arg(k, 2, a2);
      set_kernel_arg(k, 3, a3);
      set_kernel_arg(k, 4, a4);
      set_kernel_arg(k, 5, a5);
      set_kernel_arg(k, 6, a6);
      set_kernel_arg(k, 7, a7);
      set_kernel_arg(k, 8, a8);
      set_kernel_arg(k, 9, a9);
      set_kernel_arg(k, 10, a10);
      set_kernel_arg(k, 11, a11);
      set_kernel_arg(k, 12, a12);
      set_kernel_arg(k, 13, a13);
      set_kernel_arg(k, 14, a14);
      set_kernel_arg(k, 15, a15);
      set_kernel_arg(k, 16, a16);
    }

};

#endif
