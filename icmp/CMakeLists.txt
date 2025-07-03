add_executable(fuzz_process_icmp
  main.c
  callbacks.c
  ${freertos_kernel_SOURCE_DIR}/portable/MemMang/heap_5.c)

target_link_libraries(fuzz_process_icmp PUBLIC freertos_plus_tcp freertos_kernel freertos_config)
