	# Minimum CMake version required, we'll just use the latest version.
	cmake_minimum_required(VERSION 3.22)
	# Project name, version and description
    project(DynamikIP_ServerBot VERSION 1.0 DESCRIPTION "This is a light-weight Discord Bot for Servers, which updates you about the current **IPv4/IPv6** address of your Server.
Perfect for a Minecraft-Server, if you don't want to buy a Domain-Name.
")
	 
	 list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
	  
	 # Create an executable
	 add_executable(${PROJECT_NAME}
	     src/main.cpp
	 )
	  
	 # Find our pre-installed DPP package (using FindDPP.cmake).
	 find_package(DPP REQUIRED)
	  
	 # Link the pre-installed DPP package.
	 target_link_libraries(${PROJECT_NAME} 
	     ${DPP_LIBRARIES}
	 )
	  
	 # Include the DPP directories.
	 target_include_directories(${PROJECT_NAME} PRIVATE
	     ${DPP_INCLUDE_DIR}
         include
	 )
	  
	 # Set C++ version
	 set_target_properties(${PROJECT_NAME} PROPERTIES
	     CXX_STANDARD 20
	     CXX_STANDARD_REQUIRED ON
	 )
