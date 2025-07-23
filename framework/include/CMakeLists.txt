# framework/include/CMakeLists.txt

# header-only libraries
add_library(asocket_lib INTERFACE)
add_library(factory_lib INTERFACE)
add_library(icommand_lib INTERFACE)
add_library(itp_task_lib INTERFACE)
add_library(ilistener_lib INTERFACE)
add_library(itask_args_lib INTERFACE)
add_library(udp_socket_lib INTERFACE)
add_library(iinput_proxy_lib INTERFACE)
add_library(waitable_queue_lib INTERFACE)
add_library(ischeduler_task_lib INTERFACE)
add_library(tcp_conn_socket_lib INTERFACE)
add_library(dispatch_callback_lib INTERFACE)
add_library(ts_waitable_queue_lib INTERFACE)
add_library(tcp_listener_socket_lib INTERFACE)

# include directories
target_include_directories(asocket_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(factory_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(icommand_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(itp_task_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ilistener_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(itask_args_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(udp_socket_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(iinput_proxy_lib INTERFACE
    `                                               ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(waitable_queue_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ischeduler_task_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tcp_conn_socket_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(dispatch_callback_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ts_waitable_queue_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tcp_listener_socket_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})

# header-only dependencies
target_link_libraries(udp_socket_lib INTERFACE asocket_lib)
target_link_libraries(icommand_lib INTERFACE itask_args_lib)
target_link_libraries(tcp_conn_socket_lib INTERFACE asocket_lib)
target_link_libraries(ts_waitable_queue_lib INTERFACE waitable_queue_lib)
target_link_libraries(iinput_proxy_lib INTERFACE itask_args_lib ilistener_lib)
target_link_libraries(tcp_listener_socket_lib INTERFACE asocket_lib
                                                            tcp_conn_socket_lib)
