# concrete/include/CMakeLists.txt

# header-only libraries
add_library(uid_lib INTERFACE)
add_library(ticket_lib INTERFACE)
add_library(amessage_lib INTERFACE)
add_library(nbd_proxy_lib INTERFACE)
add_library(iresponse_lib INTERFACE)
add_library(nbd_server_lib INTERFACE)
add_library(atask_args_lib INTERFACE)
add_library(task_result_lib INTERFACE)
add_library(read_command_lib INTERFACE)
add_library(minion_proxy_lib INTERFACE)
add_library(file_manager_lib INTERFACE)
add_library(master_proxy_lib INTERFACE)
add_library(read_response_lib INTERFACE)
add_library(write_command_lib INTERFACE)
add_library(ifile_manager_lib INTERFACE)
add_library(iminion_proxy_lib INTERFACE)
add_library(write_response_lib INTERFACE)
add_library(minion_manager_lib INTERFACE)
add_library(response_manager_lib INTERFACE)
add_library(minion_read_command_lib INTERFACE)
add_library(minion_write_command_lib INTERFACE)
add_library(minion_read_task_args_lib INTERFACE)
add_library(minion_write_task_args_lib INTERFACE)

# include directories
target_include_directories(uid_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(amessage_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(nbd_proxy_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(iresponse_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(nbd_server_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(atask_args_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(task_result_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(read_command_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(minion_proxy_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(file_manager_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(master_proxy_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(read_response_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(write_command_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ifile_manager_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(iminion_proxy_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(write_response_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(minion_manager_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(response_manager_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(minion_read_command_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(minion_write_command_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(minion_read_task_args_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(minion_write_task_args_lib INTERFACE
                                                    ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ticket_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# header-only dependencies
target_link_libraries(amessage_lib INTERFACE uid_lib)
target_link_libraries(task_result_lib INTERFACE uid_lib)
target_link_libraries(iresponse_lib INTERFACE task_result_lib)
target_link_libraries(iminion_proxy_lib INTERFACE amessage_lib)
target_link_libraries(file_manager_lib INTERFACE ifile_manager_lib)
target_link_libraries(atask_args_lib INTERFACE uid_lib itask_args_lib)
target_link_libraries(master_proxy_lib INTERFACE uid_lib udp_socket_lib
                                                            iinput_proxy_lib)
target_link_libraries(minion_read_command_lib INTERFACE icommand_lib)
target_link_libraries(minion_write_command_lib INTERFACE icommand_lib)
target_link_libraries(minion_read_task_args_lib INTERFACE uid_lib
                                                                itask_args_lib)
target_link_libraries(minion_write_task_args_lib INTERFACE uid_lib
                                                                itask_args_lib)
target_link_libraries(ticket_lib INTERFACE uid_lib task_result_lib
                                        iminion_proxy_lib dispatch_callback_lib)
target_link_libraries(minion_manager_lib INTERFACE ticket_lib reactor_lib)
target_link_libraries(minion_proxy_lib INTERFACE uid_lib udp_socket_lib
                                                            iminion_proxy_lib)
target_link_libraries(nbd_server_lib INTERFACE tcp_conn_socket_lib)
target_link_libraries(nbd_proxy_lib INTERFACE atask_args_lib iinput_proxy_lib
                                        dispatch_callback_lib nbd_server_lib)
target_link_libraries(read_command_lib INTERFACE icommand_lib)
target_link_libraries(write_command_lib INTERFACE icommand_lib)
target_link_libraries(read_response_lib INTERFACE iresponse_lib)
target_link_libraries(write_response_lib INTERFACE iresponse_lib)
target_link_libraries(response_manager_lib INTERFACE ticket_lib nbd_proxy_lib
                                                                iresponse_lib)
