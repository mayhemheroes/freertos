add_library(middleware OBJECT
  callbacks.c
  ${freertos_kernel_SOURCE_DIR}/portable/MemMang/heap_5.c
)

target_link_libraries(middleware
  PUBLIC
  freertos_kernel
  freertos_plus_tcp
  freertos_config)
