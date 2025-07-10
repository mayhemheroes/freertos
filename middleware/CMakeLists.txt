add_library(middleware OBJECT
  callbacks.c
  network.c
  ${freertos_kernel_SOURCE_DIR}/portable/MemMang/heap_3.c
)

target_link_libraries(middleware
  PUBLIC
  freertos_kernel
  freertos_plus_tcp
  freertos_config)
