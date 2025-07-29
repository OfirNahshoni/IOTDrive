# concrete/test/CMakeLists.txt

# include test_macros
include_directories(${CMAKE_SOURCE_DIR}/framework/test)

# executables
add_executable(test_amessage TestAMessageOfirst.cpp)
add_executable(minion1 TestDemoMinion1.cpp)
add_executable(minion2 TestDemoMinion2.cpp)
add_executable(master TestMaster.cpp)
add_executable(create_demo_file Create8MBFile.cpp)

# link libraries to executables
target_link_libraries(test_amessage PRIVATE amessage_static_lib uid_static_lib)
target_link_libraries(minion1 PRIVATE factory_lib amessage_static_lib
            framework_static_lib itask_args_lib handleton_shared_lib
            file_manager_static_lib master_proxy_static_lib
            minion_read_command_static_lib minion_write_command_static_lib
            asocket_static_lib udp_socket_static_lib
            read_response_static_lib uid_static_lib write_response_static_lib
            reactor_static_lib)

target_link_libraries(minion2 PRIVATE factory_lib amessage_static_lib
            framework_static_lib itask_args_lib handleton_shared_lib
            file_manager_static_lib master_proxy_static_lib
            minion_read_command_static_lib minion_write_command_static_lib
            asocket_static_lib udp_socket_static_lib
            read_response_static_lib uid_static_lib write_response_static_lib
            reactor_static_lib)

target_link_libraries(master PRIVATE factory_lib nbd_proxy_static_lib
            framework_static_lib nbd_server_static_lib itask_args_lib
            minion_proxy_static_lib read_command_static_lib
            write_command_static_lib minion_manager_static_lib
            response_manager_static_lib uid_static_lib
            tcp_conn_socket_static_lib udp_socket_static_lib ticket_static_lib
            read_response_static_lib write_response_static_lib
            task_result_static_lib)
