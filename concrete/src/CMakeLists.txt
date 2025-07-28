# concrete/src/CMakeLists.txt

# static libraries
add_library(uid_static_lib STATIC UID.cpp)
add_library(ticket_static_lib STATIC Ticket.cpp)
add_library(amessage_static_lib STATIC AMessage.cpp)
add_library(nbd_proxy_static_lib STATIC NBDProxy.cpp)
add_library(nbd_server_static_lib STATIC NBDServer.cpp)
add_library(atask_args_static_lib STATIC ATaskArgs.cpp)
add_library(task_result_static_lib STATIC TaskResult.cpp)
add_library(file_manager_static_lib STATIC FileManager.cpp)
add_library(master_proxy_static_lib STATIC MasterProxy.cpp)
add_library(minion_proxy_static_lib STATIC MinionProxy.cpp)
add_library(read_command_static_lib STATIC ReadCommand.cpp)
add_library(read_response_static_lib STATIC ReadResponse.cpp)
add_library(write_command_static_lib STATIC WriteCommand.cpp)
add_library(write_response_static_lib STATIC WriteResponse.cpp)
add_library(minion_manager_static_lib STATIC MinionManager.cpp)
add_library(response_manager_static_lib STATIC ResponseManager.cpp)
add_library(minion_read_command_static_lib STATIC Minion_ReadCommand.cpp)
add_library(minion_write_command_static_lib STATIC Minion_WriteCommand.cpp)
add_library(minion_read_task_args_static_lib STATIC Minion_ReadTaskArgs.cpp)
add_library(minion_write_task_args_static_lib STATIC Minion_WriteTaskArgs.cpp)

# link libraries
target_link_libraries(uid_static_lib PRIVATE uid_lib)
target_link_libraries(ticket_static_lib PRIVATE ticket_lib)
target_link_libraries(task_result_static_lib PRIVATE task_result_lib)
target_link_libraries(read_response_static_lib PRIVATE read_response_lib
                        iresponse_lib handleton_shared_lib nbd_proxy_static_lib)
target_link_libraries(write_response_static_lib PRIVATE write_response_lib
                        iresponse_lib handleton_shared_lib nbd_proxy_static_lib)
target_link_libraries(nbd_server_static_lib PRIVATE nbd_server_lib
                                                            logger_static_lib)
target_link_libraries(nbd_proxy_static_lib PRIVATE nbd_proxy_lib factory_lib
                                                        handleton_shared_lib)
target_link_libraries(minion_proxy_static_lib PRIVATE minion_proxy_lib
                                            factory_lib handleton_shared_lib)
target_link_libraries(minion_read_task_args_static_lib PRIVATE
                                                    minion_read_task_args_lib)
target_link_libraries(minion_write_task_args_static_lib PRIVATE
                                                    minion_write_task_args_lib)
target_link_libraries(amessage_static_lib PRIVATE amessage_lib)
target_link_libraries(minion_manager_static_lib PRIVATE minion_manager_lib
                                    amessage_static_lib handleton_shared_lib)
target_link_libraries(atask_args_static_lib PRIVATE atask_args_lib
                                                            logger_static_lib)
target_link_libraries(response_manager_static_lib PRIVATE response_manager_lib
            minion_manager_static_lib atask_args_static_lib nbd_proxy_static_lib
                factory_lib read_response_static_lib write_response_static_lib)
target_link_libraries(read_command_static_lib PRIVATE read_command_lib
            handleton_shared_lib atask_args_static_lib minion_manager_static_lib
                                                    response_manager_static_lib)
target_link_libraries(write_command_static_lib PRIVATE write_command_lib
            handleton_shared_lib atask_args_static_lib minion_manager_static_lib
                                                    response_manager_static_lib)
target_link_libraries(file_manager_static_lib PRIVATE file_manager_lib)
target_link_libraries(master_proxy_static_lib PRIVATE amessage_static_lib
                            master_proxy_lib minion_read_task_args_static_lib
                                            minion_write_task_args_static_lib)
target_link_libraries(minion_read_command_static_lib PRIVATE
        handleton_shared_lib file_manager_static_lib master_proxy_static_lib
                    minion_read_command_lib minion_read_task_args_static_lib)
target_link_libraries(minion_write_command_static_lib PRIVATE
        handleton_shared_lib file_manager_static_lib master_proxy_static_lib
                    minion_write_command_lib minion_write_task_args_static_lib)
