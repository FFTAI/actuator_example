include_directories(${PROJECT_SOURCE_DIR}/include)



# Find all *.cpp files and store in list native_srcs
# file(GLOB_RECURSE native_srcs RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
# foreach(srcfile IN LISTS native_srcs)
#     # Get file name without directory
#     get_filename_component(elfname ${srcfile} NAME_WE)
#     add_executable(${elfname} ${srcfile} fse.cpp os.cpp logger.cpp)
# endforeach()

# add_executable(demo_reboot demo_reboot.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_reboot_fse demo_reboot_fse.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_ota demo_ota.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_ota_test demo_ota_test.cpp fse.cpp os.cpp logger.cpp)

# add_executable(demo_ota_cloud demo_ota_cloud.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_lookup demo_lookup.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_lookup_AbsEncoder demo_lookup_AbsEncoder.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_home_position_set demo_home_position_set.cpp fse.cpp os.cpp logger.cpp)

# add_executable(demo_home_offset_set demo_home_offset_set.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_home_offset_get demo_home_offset_get.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_get_measured demo_get_measured.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_ctrl_config_set demo_ctrl_config_set.cpp fse.cpp os.cpp logger.cpp)

# add_executable(demo_ctrl_config_save demo_ctrl_config_save.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_ctrl_config_get demo_ctrl_config_get.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_comm_config_set demo_comm_config_set.cpp fse.cpp os.cpp logger.cpp)
# add_executable(demo_comm_config_get demo_comm_config_get.cpp fse.cpp os.cpp logger.cpp)


set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)